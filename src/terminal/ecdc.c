/**
 * Copyright (c) 2016 Bradley Kim Schleusner < bradschl@gmail.com >
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "ecdc.h"

   

struct ecdc_console * dbg_Terminal = NULL;   // allocate console in heap 

// ------------------------------------------------------------ Private settings

// Size of the control sequence buffer. There is no upper bound specified
// in a standard, but we can assume that we won't have to process any of the
// really complex ones. That is mostly the terminals problem
#define CS_BUFFER_SIZE                  16

// Default command prompt. This is a raw string, and will not go through
// normal special character replacement before being written out (for
// performance reasons)
#define DEFAULT_PROMPT                  " # "


// -------------------------------------------------------------- Private types

typedef void (*console_state_fn)(struct ecdc_console *);


struct ecdc_command {
    // Command linked list storage
    struct ecdc_command *               next;
    struct ecdc_console *               console;


    // Callback
    ecdc_callback_fn                    callback;
    void *                              hint;


    // Command info
    char *                              name;
};


struct ecdc_console {
    // Command linked list root pointer
    struct ecdc_command *               root;


    // Argument line storage
    char *                              arg_line;
    size_t                              arg_line_size;
    size_t                              arg_line_write_index;


    // Argument pointer storage
    const char **                       argv;
    size_t                              max_argc;


    // Console read / write
    ecdc_getc_fn                        getc;
    ecdc_puts_fn                        puts;
    void *                              hint;
    int                                 snoop_char;


    // State machine
    console_state_fn                    state;


    // Control sequence handling
    char                                cs_buffer[CS_BUFFER_SIZE];
    size_t                              cs_write_index;


    // Flags and settings
    bool                                f_local_echo;
    enum ecdc_mode                      mode;

    // Prompt
    char  *                             prompt;
};


// ---------------------------------------------------------- Private functions

static inline char *
ecdc_strdup(const char * s)
{
    #if defined(strdup)
        return strdup(s);
    #else
        char * new_s = NULL;
        if(NULL != s) {
            size_t len = strlen(s) + 1;
            new_s = (char *)malloc(len);
            if(NULL != new_s) {
                memcpy(new_s, s, len);
            }
        }
        return new_s;
    #endif
}


static struct ecdc_command *
locate_command(struct ecdc_console * console,
               const char * name)
{
    struct ecdc_command * ret = NULL;

    if(NULL != console) {
        struct ecdc_command * node = NULL;
        for(node = console->root; NULL != node; node = node->next) {
            if(0 == strcmp(node->name, name)) {
                ret = node;
                break;
            }
        }
    }

    return ret;
}

static struct ecdc_command *
get_last_command(struct ecdc_console * console)
{
    struct ecdc_command * last_command = NULL;

    if(NULL != console) {
        for(last_command = console->root;
            NULL != last_command;
            last_command = last_command->next) {

            if(NULL == last_command->next) {
                break;
            }
        }
    }

    return last_command;
}

static struct ecdc_command *
get_previous_command(struct ecdc_command * command)
{
    struct ecdc_command * prev = NULL;
    do {
        if(NULL == command) {
            break;
        }

        struct ecdc_console * console = command->console;
        if(NULL == console) {
            break;
        }

        if(console->root == command) {
            break;
        }

        struct ecdc_command * node = NULL;
        for(node = console->root; node != NULL; node = node->next) {
            if(command == node->next) {
                prev = node;
                break;
            }
        }

    } while(0);

    return prev;
}

static void
register_command(struct ecdc_console * console,
                 struct ecdc_command * command)
{
    if(NULL != console) {
        command->console = console;
        command->next = NULL;

        struct ecdc_command * last_command = get_last_command(console);
        if(NULL == last_command) {
            console->root = command;
        }
        else {
            last_command->next = command;
        }
    }
}

static void
unregister_command(struct ecdc_command * command)
{
    do {
        if(NULL == command) {
            break;
        }

        struct ecdc_console * console = command->console;
        if(NULL == console) {
            break;
        }

        if(console->root == command) {
            console->root = command->next;
        }
        else {
            struct ecdc_command * prev = get_previous_command(command);
            if(NULL != prev)
            {
                prev->next = command->next;
            }
        }

        command->console = NULL;
        command->next = NULL;
    } while(0);
}

static char *
find_first_non_whitesapce(char * str)
{
    char * out_ptr = NULL;
    if(str == NULL) {
        goto out;
    }

    while(*str != '\0') {
        switch(*str) {
            case '\x20':
            case '\x09':
            case '\x0A':
            case '\x0B':
            case '\x0C':
            case '\x0D':
                ++str;
                break;
            default:
                out_ptr = str;
                goto out;
        }
    }

    out:
        return out_ptr;
}

static char *
find_fist_whitespace(char * str)
{
    char * out_ptr = NULL;
    if(str == NULL) {
        goto out;
    }

    while(*str != '\0') {
        switch(*str) {
            case '\x20':
            case '\x09':
            case '\x0A':
            case '\x0B':
            case '\x0C':
            case '\x0D':
                out_ptr = str;
                goto out;
            default:
                ++str;
                break;
        }
    }

    out:
        return out_ptr;
}


// --------------------------------------------------------- Terminal functions

// ---------------------------- Newline

static void
term_put_ansi_newline(struct ecdc_console * console)
{
    const char * newline_seq = "\r\n";
    console->puts(console->hint, newline_seq, 2);
}

static inline void
term_put_newline(struct ecdc_console * console)
{
    switch(console->mode) {
        case ECDC_MODE_ANSI:
        default:
            term_put_ansi_newline(console);
            break;
    }
}


// -------------------------- Backspace

static inline void
term_backspace_ansi(struct ecdc_console * console)
{
    const char * backspace_seq = "\x08\x20\x08"; // BS, SP, BS
    console->puts(console->hint, backspace_seq, 3);
}

static inline void
term_backspace(struct ecdc_console * console)
{
    switch(console->mode) {
        case ECDC_MODE_ANSI:
        default:
            term_backspace_ansi(console);
            break;
    }
}


//------------------- Character writing

static void
term_puts(struct ecdc_console * console, const char * str)
{
    if(NULL == str) {
        return;
    }

    while(*str != '\0') {
        bool seq_end_with_nl = false;
        bool seq_end_with_bs = false;

        const char * end_seq;
        for(end_seq = str; *end_seq != '\0'; ++end_seq) {
            if('\n' == *end_seq) {
                seq_end_with_nl = true;
                break;
            } else if('\x08' == *end_seq) {
                seq_end_with_bs = true;
                break;
            }
        }

        if(end_seq != str) {
            size_t seq_len = end_seq - str;
            console->puts(console->hint, str, seq_len);
            str = end_seq;
        }

        if(seq_end_with_nl) {
            term_put_newline(console);
            ++str;
        } else if(seq_end_with_bs) {
            term_backspace(console);
            ++str;
        }
    }
}

static inline void
term_putc(struct ecdc_console * console, char c)
{
    if('\n' == c) {
        term_put_newline(console);
    } else if('\x08' == c) {
        term_backspace(console);
    } else {
        console->puts(console->hint, &c, 1);
    }
}

static inline void
term_puts_raw(struct ecdc_console * console, const char * s, size_t len)
{
    console->puts(console->hint, s, len);
}

static inline void
term_putc_raw(struct ecdc_console * console, char c)
{
    console->puts(console->hint, &c, 1);
}


// ------------------ Character reading

static inline int
term_getc_raw(struct ecdc_console * console)
{
    int ret = console->snoop_char;
    console->snoop_char = ECDC_GETC_EOF;

    if(ECDC_GETC_EOF == ret) {
        ret = console->getc(console->hint);
    }

    return ret;
}

static inline void
term_set_snoop_char(struct ecdc_console * console, char c)
{
    console->snoop_char = c;
}


// ---------------------------------------------------- State machine functions

static void
state_start_new_command(struct ecdc_console * console);

static void
state_read_input(struct ecdc_console * console);


static void
state_parse_escape_sequence_ansi(struct ecdc_console * console)
{
    // TODO: Stub
    // This would be a great spot to handle arrow keys
    console->state = state_read_input;
}

static void
state_read_escape_sequence(struct ecdc_console * console)
{
    bool abort_sequence = false;
    bool parse_sequence = false;

    int loop_limit;
    for(loop_limit = 0; loop_limit < 8; ++loop_limit)
    {
        int new_char = term_getc_raw(console);
        if(ECDC_GETC_EOF == new_char) {
            break;
        }

        char in = new_char;

        if(('\x18' == in) || ('\x1A' == in)) {
            // CAN or SUB
            abort_sequence = true;
            break;
        } else if(console->cs_write_index < CS_BUFFER_SIZE) {
            console->cs_buffer[console->cs_write_index] = in;
            size_t index = console->cs_write_index;
            ++console->cs_write_index;

            if(1 == index) {
                if('[' == in) {
                    // Control sequence introducer, this will be a 3 or more
                    // character sequence
                } else if(('\x40' <= in) && ('\x5F' >= in)) {
                    // End of a two character escape sequence
                    parse_sequence = true;
                    break;
                }
            } else if(1 < index) {
                if(('\x40' <= in) && ('\x7E' >= in)) {
                    // End of a multi character sequence
                    parse_sequence = true;
                    break;
                }
            }
        } else {
            // Dump the sequence, parsing it would be meaningless
            term_set_snoop_char(console, in);
            abort_sequence = true;
            break;
        }
    }

    if(abort_sequence) {
        size_t i;
        for(i = 0; i < console->cs_write_index; ++i) {
            term_putc_raw(console, console->cs_buffer[i]);
        }
        console->cs_write_index = 0;
        console->state = state_read_input;
    } else if(parse_sequence) {
        switch(console->mode) {
            case ECDC_MODE_ANSI:
            default:
                console->state = state_parse_escape_sequence_ansi;
                break;
        }
    }
}

static void
state_parse_input(struct ecdc_console * console)
{
    // Split
    size_t argc = 0;
    {
        char * arg_line = console->arg_line;
        arg_line[console->arg_line_write_index] = '\0';

        size_t i = 0;
        for(; i < console->max_argc; ++i) {
            char * start = find_first_non_whitesapce(arg_line);
            if(NULL == start) {
                // Reached the \0 at the end of the string
                break;
            }

            console->argv[i] = start;
            argc = i + 1;

            char * stop = find_fist_whitespace(start);
            if(NULL == stop) {
                // Reached the \0 at the end of the string
                break;
            }
            *stop = '\0';
            arg_line = stop + 1;
        }
    }

    // Clear the rest of argv
    {
        size_t i;
        for(i = argc; i < console->max_argc; ++i) {
            console->argv[i] = NULL;
        }
    }

    // Search for handler
    if(argc > 0) {
        struct ecdc_command * command = locate_command(console, console->argv[0]);
        if(NULL != command) {
            // Found
            command->callback(command->hint, argc, console->argv);
        } else {
            term_puts(console, "'");
            term_puts(console, console->argv[0]);
            term_puts(console, "' not found\n");
        }
    }

    console->state = state_start_new_command;
}

static void
state_read_input(struct ecdc_console * console)
{
    int loop_limit;
    for(loop_limit = 0; loop_limit < 8; ++loop_limit)
    {
        int new_char = term_getc_raw(console);
        if(ECDC_GETC_EOF == new_char) {
            break;
        }

        bool local_echo = false;

        char in = new_char;
        if('\r' == in) {
            term_put_newline(console);
            console->state = state_parse_input;
            break;
        } else if('\x00' == in) {
            // Nothing to do here
        } else if(('\x08' == in) || ('\x7F' == in)) {
            // Backspace
            // This stuff gets super weird, apparently everyone on the planet
            // screwed up how backspace and delete work. See
            // http://www.ibb.net/~anne/keyboard.html for the full train wreck
            if(console->arg_line_write_index > 0) {
                term_backspace(console);
                --console->arg_line_write_index;
            }
        } else if('\x1B' == in) {
            // Start of a control sequence
            term_set_snoop_char(console, in);
            console->cs_write_index = 0;
            console->state = state_read_escape_sequence;
        } else if('\x1F' < in) {
            // Non-control sequence characters
            if(console->arg_line_write_index < console->arg_line_size) {
                console->arg_line[console->arg_line_write_index] = in;
                ++console->arg_line_write_index;
                local_echo = console->f_local_echo;
            }
        }

        if(local_echo) {
            term_putc_raw(console, in);
        }
    }
}

static void
state_start_new_command(struct ecdc_console * console)
{
    // Clear input string
    console->arg_line_write_index = 0;

    // Clear argv
    {
        size_t i;
        for(i = 0; i < console->max_argc; ++i) {
            console->argv[i] = NULL;
        }
    }

    // Set new state to read user input
    if(NULL == console->prompt)
    {
        term_puts_raw(console, DEFAULT_PROMPT,
            sizeof(DEFAULT_PROMPT) / sizeof(*DEFAULT_PROMPT));
    }
    else
    {
        term_puts(console, console->prompt);
    }

    console->state = state_read_input;
}

static void
state_wait_for_client(struct ecdc_console * console)
{
    int in = term_getc_raw(console);
    if(ECDC_GETC_EOF != in) {
        term_set_snoop_char(console, in);
        console->state = state_start_new_command;
    }
}


// ---------------------------------------------------------- Build in commands

static void
built_in_list_command(void * hint, int argc, char const * argv[])
{
    (void) argc;
    (void) argv;

    struct ecdc_console * console = (struct ecdc_console *) hint;

    struct ecdc_command * command;
    for(command = console->root; NULL != command; command = command->next) {
        term_puts(console, command->name);
        term_put_newline(console);
    }
}


// ----------------------------------------------------------- Public functions

struct ecdc_console *
ecdc_alloc_console(void * console_hint,
                   ecdc_getc_fn getc_fn,
                   ecdc_puts_fn puts_fn,
                   size_t max_arg_line_length,
                   size_t max_arg_count)
{
    struct ecdc_console * console =
        (struct ecdc_console *) malloc(sizeof(struct ecdc_console));
    if(NULL == console) {
        goto out;
    }

    console->root = NULL;
    console->getc = getc_fn;
    console->puts = puts_fn;
    console->hint = console_hint;
    console->snoop_char = ECDC_GETC_EOF;
    console->state = state_wait_for_client;
    console->prompt = NULL;

    if(max_arg_line_length < 16) {
        max_arg_line_length = 16;
    }
    console->arg_line_size = max_arg_line_length;
    console->arg_line_write_index = 0;

    size_t alloc_size = (max_arg_line_length + 1) * sizeof(char);
    console->arg_line = (char *) malloc(alloc_size);
    if(NULL == console->arg_line) {
        goto out_arg_line_fail;
    }


    if(max_arg_count < 1) {
        max_arg_count = 1;
    }
    console->max_argc = max_arg_count;

    console->argv = (const char **) malloc(sizeof(char *) * max_arg_count);
    if(NULL == console->argv) {
        goto out_argv_fail;
    }

    size_t i;
    for(i = 0; i < max_arg_count; ++i) {
        console->argv[i] = NULL;
    }


    // Initialize control sequence
    console->cs_write_index = 0;
    for(i = 0; i < CS_BUFFER_SIZE; ++i) {
        console->cs_buffer[i] = '\x00';
    }


    // Set default settings
    ecdc_configure_console(console, ECDC_MODE_ANSI, ECDC_SET_LOCAL_ECHO);


    // Success
    goto out;

    out_argv_fail:
        free(console->arg_line);

    out_arg_line_fail:
        free(console);
        console = NULL;

    out:
        return console;
}

void
ecdc_free_console(struct ecdc_console * console)
{
    if(console != NULL) {
        while(NULL != console->root) {
            unregister_command(console->root);
        }

        free(console->argv);
        free(console->arg_line);
        free(console->prompt);
        free(console);
    }
}

void
ecdc_pump_console(struct ecdc_console * console)
{
    if(NULL != console)
    {
        console->state(console);
    }
}

void
ecdc_configure_console(struct ecdc_console * console,
                       enum ecdc_mode mode,
                       int flags)
{
    if(NULL != console) {
        console->mode = mode;

        console->f_local_echo = (ECDC_SET_LOCAL_ECHO & flags) ? true : false;
    }
}

void
ecdc_replace_prompt(struct ecdc_console *console,
                    char const *prompt)
{
    if(NULL != console) {
        // If the prompt was previously not set, it will be NULL which will not
        // have any ill side effects when calling free
        free(console->prompt);

        if(NULL != prompt) {
            console->prompt = ecdc_strdup(prompt);
        } else {
            console->prompt = NULL;
        }
    }
}

struct ecdc_command *
ecdc_alloc_command(void * command_hint,
                   struct ecdc_console * console,
                   const char * command_name,
                   ecdc_callback_fn callback)
{
    struct ecdc_command * command = NULL;

    do {
        if(NULL == command_name) {
            break;
        }

        if(NULL != locate_command(console, command_name)) {
            break;
        }

        command = (struct ecdc_command *) malloc(sizeof(struct ecdc_command));
        if(NULL == command) {
            break;
        }

        command->console = NULL;
        command->next = NULL;
        command->callback = callback;
        command->hint = command_hint;

        command->name = ecdc_strdup(command_name);

        register_command(console, command);
    } while(0);

    return command;
}

void
ecdc_free_command(struct ecdc_command * command)
{
    if(NULL != command) {
        unregister_command(command);

        free(command->name);
        free(command);
    }
}

struct ecdc_command *
ecdc_alloc_list_command(struct ecdc_console * console,
                        const char * command_name)
{
    return ecdc_alloc_command(console,
                              console,
                              command_name,
                              built_in_list_command);
}

void ecdc_putc(struct ecdc_console * console, char c)
{
    if(NULL != console) {
        term_putc(console, c);
    }
}

void ecdc_puts(struct ecdc_console * console, const char * str)
{
    if(NULL != console) {
        term_puts(console, str);
    }
}

#include "ecdc_commands.h"
#include "xprint.h"

/** Отладка BLE по умолчанию включена поскольку так лучше подключается к пульту. **/
bool Terminal_debug_bluethooth = true;
extern struct ecdc_console * dbg_Terminal;

static void  enter_debug_clbk(void * hint, int argc, char const * argv[])
{
    Terminal_debug_bluethooth = true;
    xprintln("BLE debugging via terminal is enabled.");
}

static void  exit_debug_clbk(void * hint, int argc, char const * argv[])
{
    Terminal_debug_bluethooth = false;
    xprintln("BLE debugging via terminal is disabled.");
}

static void  test_uart_clbk(void * hint, int argc, char const * argv[])
{
    xprintln("%d", 1234);			// "1234"
    xprintln("%6d,%3d%%", -200, 5);	// "  -200,  5%"
    xprintln("%-6u", 100);			// "100   "
    xprintln("%ld", 12345678L);		// "12345678"
    xprintln("%04x", 0xA3);			// "00a3"
    xprintln("%08LX", 0x123ABC);	// "00123ABC"
    xprintln("%016b", 0x550F);		// "0101010100001111"
    xprintln("%s", "String");		// "String"
    xprintln("%-4s", "abc");		// "abc "
    xprintln("%4s", "abc");			// " abc"
    xprintln("%c", 'a');			// "a"
    xprintln("%f", 10.0);           // lacks floating point support use this instead print.ln(10.0567, 4);
    xprintln("This is wery long long long string...");
    xprintln("AaBbCcDdEeFfGgHhJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz 0123456789");
}

static void  help_clbk(void * hint, int argc, char const * argv[])
{
    xprintln("list of commands:");
    xprintln("enterdbg - entering BLE debuging mode.");
    xprintln("exitdbg  - exit BLE debuging mode.");
    xprintln("uarttst  - print test of xprintf function.");
}

void setup_ecdc_commands(struct ecdc_console * console)
{
    if(console != NULL)
    {
        ecdc_configure_console(dbg_Terminal, ECDC_MODE_ANSI, ECDC_SET_LOCAL_ECHO);
        
        // allocate commands in heap
        struct ecdc_command * enter_debug_cmd =  ecdc_alloc_command(NULL, console, "enterdbg", enter_debug_clbk);
        struct ecdc_command * exit_debug_cmd =  ecdc_alloc_command(NULL, console, "exitdbg", exit_debug_clbk); 
        struct ecdc_command * help_cmd =  ecdc_alloc_command(NULL, console, "help", help_clbk);
        struct ecdc_command * test_uart_cmd =  ecdc_alloc_command(NULL, console, "uarttst", test_uart_clbk);
        
        xprintln("Application started! Terminal is available. Type 'help' for more info.");
    }
}
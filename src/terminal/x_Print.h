#ifndef _X_PRINT_H
#define _X_PRINT_H

#include <string>
#include <stdarg.h>
#include "n_UART.h"
#include "UART_DT_driver.h"

class AM335x_UART;
class UART_DT_driver;

enum e_DW_BASE : uint32_t
{
    DW_BIN = 2,
    DW_OCT = 8,
    DW_DEC = 10,
    DW_HEX = 16
};

enum e_DW_SIZE : uint32_t
{
    DW_CHAR = sizeof(char),
    DW_SHORT = sizeof(short),
    DW_LONG	= sizeof(long)
};

/**----------------------------------------------**/
/** Formatted string output                      **/
/**----------------------------------------------**/
/** 
    print.ln("%d", 1234);			// "1234"
    print.ln("%6d,%3d%%", -200, 5);	// "  -200,  5%"
    print.ln("%-6u", 100);			// "100   "
    print.ln("%ld", 12345678L);		// "12345678"
    print.ln("%04x", 0xA3);			// "00a3"
    print.ln("%08LX", 0x123ABC);	// "00123ABC"
    print.ln("%016b", 0x550F);		// "0101010100001111"
    print.ln("%s", "String");		// "String"
    print.ln("%-4s", "abc");		// "abc "
    print.ln("%4s", "abc");			// " abc"
    print.ln("%c", 'a');			// "a"
    print.ln("%f", 10.0);           // lacks floating point support 
    print.ln(10.0567, 4);           // use this instead
**/

class x_Print : public UART_client_ops
{
public:
                  x_Print(UART_DT_Driver *p_Serial) 
                  : m_Write_error(0), m_Serial(*p_Serial)  {}
 
            inline char  read(const char *data, size_t len)
            { 
                return UART_client_ops::read((void *)UART_client_ops::p_UART_instance);            
            }
            
            inline int  write(const char *data, size_t len)
            { 
                return UART_client_ops::write((void *)UART_client_ops::p_UART_instance, data, len);            
            }
            
            inline void  write(char c)
            {
                write(&c,1);
            } 
            
            inline void  write(const char *s)
            {
                if (s == NULL) 
                    return;

                volatile uint32_t len = strlen(s);

                write(s, len);  
            }
            
            void  f(const std::string &); 
            void  f(const char* fmt, ...);
            void  f(char);
            void  f(unsigned char, e_DW_BASE = DW_DEC);
            void  f(int, e_DW_BASE = DW_DEC);
            void  f(unsigned int, e_DW_BASE = DW_DEC);
            void  f(long, e_DW_BASE = DW_DEC);
            void  f(unsigned long, e_DW_BASE = DW_DEC);
            void  f(double, int = 2);
            
            void  ln(const std::string &);
            void  ln(const char* fmt, ...);
            void  ln(char);
            void  ln(unsigned char, e_DW_BASE = DW_DEC);
            void  ln(int, e_DW_BASE = DW_DEC);
            void  ln(unsigned int, e_DW_BASE = DW_DEC);
            void  ln(long, e_DW_BASE = DW_DEC);
            void  ln(unsigned long, e_DW_BASE = DW_DEC);
            void  ln(double, int = 2);
            void  ln();
            
            void dump (const void* buff, int len, unsigned long addr = 0UL, e_DW_SIZE width = DW_CHAR); // Dump a line of binary dump  

    virtual void  flush() { /* Empty implementation for backward compatibility */ }
            // default to zero, meaning "a single write may block"
            // should be overriden by subclasses with buffering
    virtual bool  available_for_write(void) { return 0; } 
             int  get_write_error()   { return m_Write_error; }
            void  clear_write_error() { set_write_error(0); }
            void  set_write_error(int err = 1) { m_Write_error = err; }
            void  vf (const char*	fmt,	    // Pointer to the format string
                           va_list arp   );	    // Pointer to arguments
private:
  
  UART_DT_Driver &m_Serial;
             int  m_Write_error;
            void  m_Print_number(unsigned long, uint8_t);
            void  m_Print_float(double, uint8_t);
};

extern x_Print print;
#endif // _X_PRINT_H
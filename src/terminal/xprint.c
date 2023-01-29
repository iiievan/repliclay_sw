#include "include.h"
#include "xprint.h"
#include "x_Print.h"

#ifdef __cplusplus
extern "C" {
#endif

void xprintf(const char* fmt, ...)
{
    va_list arp;

    va_start(arp, fmt);
    print.vf(fmt, arp);
    va_end(arp);
}

void xprintln(const char* fmt, ...)
{
    va_list arp;

    va_start(arp, fmt);
    print.vf(fmt, arp);
    va_end(arp);
    print.ln();
}

void xprint_dump(const void* buff,		// Pointer to the array to be dumped
                 int len,				// Number of items to be dumped 
                 unsigned long addr,    // Heading address value                    
                 int width)		        // Size of the items (DW_CHAR, DW_SHORT, DW_LONG)
{
    print.dump(buff, len, addr, (e_DW_SIZE)width);   // DW_CHAR by default
}

uint64_t get_ms()
{
    return sys_tmr.get_mseconds();
}

#ifdef __cplusplus
}
#endif
#ifndef _XPRINT_H 
#define _XPRINT_H 

// это С обертка для класса x_Print
#ifdef __cplusplus
extern "C" {
#endif
  
#define    DW_CHAR sizeof(char)
#define    DW_SHORT sizeof(short)
#define    DW_LONG	sizeof(long)
  
extern void xprintf(const char* fmt, ...);
extern void xprintln(const char* fmt, ...);
extern void xprint_dump(const void*  buff,		// Pointer to the array to be dumped
                                int  len,		// Number of items to be dumped 
                      unsigned long  addr,      // Heading address value                    
                                int  width);	// Size of the items (DW_CHAR, DW_SHORT, DW_LONG)
extern uint64_t get_ms();

#ifdef __cplusplus
}
#endif


#endif
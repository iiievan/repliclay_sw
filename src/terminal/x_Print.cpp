#include "include.h"
#include "x_Print.h"

void x_Print::f(const std::string &s)
{    
    m_Serial.write(s.c_str(), s.length());
}

void x_Print::f(const char* fmt,	// Pointer to the format string
                ...)			    // Optional arguments 
{
	va_list arp;

	va_start(arp, fmt);
	vf(fmt, arp);
	va_end(arp);
}

void x_Print::f(char c)
{  
    m_Serial.write(c);
}

void x_Print::f(unsigned char c, e_DW_BASE base)
{
    f((unsigned long) c, base);
}

void x_Print::f(int n, e_DW_BASE base)
{
    f((long)n, base);
}

void x_Print::f(unsigned int n, e_DW_BASE base)
{    
    f((unsigned long)n, base);
}

void x_Print::f(long n, e_DW_BASE base)
{ 
    if (base == 0) 
        m_Serial.write(n);
    else 
    if (base == 10) 
    {
        if (n < 0) 
        {
            f('-');
            n = -n;
            m_Print_number(n, 10);
        }
    
        m_Print_number(n, 10);    
    } 
    else 
        m_Print_number(n, base);
}

void x_Print::f(unsigned long n, e_DW_BASE base)
{ 
    if (base == 0) 
        m_Serial.write(n);
    else 
        m_Print_number(n, base);
}

void x_Print::f(double n, int digits)
{
    m_Print_float(n, digits);
}

void x_Print::ln(const std::string &s)
{
    f(s);
    ln();
}

void x_Print::ln(const char* fmt,	// Pointer to the format string
                 ...)			    // Optional arguments 
{
	va_list arp;

	va_start(arp, fmt);
	vf(fmt, arp);
	va_end(arp);
    ln();
}

void x_Print::ln(char c)
{
    f(c);
    ln();
}

void x_Print::ln(unsigned char c, e_DW_BASE base)
{
    f(c, base);
    ln();
}

void x_Print::ln(int num, e_DW_BASE base)
{
    f(num, base);
    ln();
}

void x_Print::ln(unsigned int num, e_DW_BASE base)
{
    f(num, base);
    ln(); 
}

void x_Print::ln(long num, e_DW_BASE base)
{
    f(num, base);
    ln(); 
}

void x_Print::ln(unsigned long num, e_DW_BASE base)
{
    f(num, base);
    ln();
}

void x_Print::ln(double num, int digits)
{
    f(num, digits);
    ln();
}

void x_Print::ln()
{  
    m_Serial.write("\r\n");
}

// Dump a line of binary dump
void x_Print::dump (const void* buff,		// Pointer to the array to be dumped
                    int len,				// Number of items to be dumped 
                    unsigned long addr,		// Heading address value                    
                    e_DW_SIZE width)		// Size of the items (DW_CHAR, DW_SHORT, DW_LONG)
{
 	int i;
	const unsigned char *bp;
	const unsigned short *sp;
	const unsigned long *lp; 
    
	ln("%08lX:", addr);		// address 

	switch (width) 
    {
	case DW_CHAR:
		bp = (unsigned char *)buff;
        
		for (i = 0; i < len; i++)		// Hexdecimal dump
			f(" %02X", bp[i]);
        
		m_Serial.write(' ');
        
		for (i = 0; i < len; i++)		// ASCII dump
			m_Serial.write((bp[i] >= ' ' && bp[i] <= '~') ? bp[i] : '.');
        
		break;
        
	case DW_SHORT:
		sp = (unsigned short *)buff;
		do								// Hexdecimal dump
			f(" %04X", *sp++);
		while (--len);
		break;
	case DW_LONG:
		lp = (unsigned long *)buff;
		do								// Hexdecimal dump
			f(" %08LX", *lp++);
		while (--len);
		break;
	}

    ln();
}

void x_Print::vf (const char*	fmt,	// Pointer to the format string
                        va_list arp)    // Pointer to arguments
{
	unsigned int r, i, j, w, f;
	unsigned long v;
	char s[16], c, d, *p;


	for (;;) 
    {
		c = *fmt++;					// Get a char
		if (!c) break;				// End of format?
        
		if (c != '%')   // Pass through it if not a % sequense
        {				
			m_Serial.write(c); 
            continue;
		}
        
		f = 0;
		c = *fmt++;					// Get first char of the sequense
		if (c == '0') 
        {				// Flag: '0' padded
			f = 1; 
            c = *fmt++;
		} 
        else 
        {
			if (c == '-') 
            {			// Flag: left justified
				f = 2; 
                c = *fmt++;
			}
		}
        
		for (w = 0; c >= '0' && c <= '9'; c = *fmt++)	// Minimum width
        {
			w = w * 10 + c - '0';
        }
        
		if (c == 'l' || c == 'L') // Prefix: Size is long int
        {	
			f |= 4; c = *fmt++;
		}
        
		if (!c)   // End of format?
            break;	
        
		d = c;
		if (d >= 'a') 
          d -= 0x20;
        
        // Type is...
		switch (d) 
        {				
		case 'S' :					// String 
			p = va_arg(arp, char*);
            
			for (j = 0; p[j]; j++);
            
			while (!(f & 2) && j++ < w) 
                m_Serial.write(' ');
            
			m_Serial.write(p);
            
			while (j++ < w) 
                m_Serial.write(' ');
            
			continue;
		case 'C' :					// Character
			m_Serial.write((char)va_arg(arp, int)); 
            continue;
		case 'B' :					// Binary
			r = 2; 
            break;
		case 'O' :					// Octal
			r = 8; 
            break;
		case 'D' :					// Signed decimal
		case 'U' :					// Unsigned decimal
			r = 10; 
            break;
		case 'X' :					// Hexdecimal 
			r = 16; 
            break;
    	case 'f' :					// float 
            break;
		default:					// Unknown type (passthrough)
			m_Serial.write(c); 
            continue;
		}

		// Get an argument and put it in numeral
		v = (f & 4) ? va_arg(arp, long) : ((d == 'D') ? (long)va_arg(arp, int) : (long)va_arg(arp, unsigned int));
        
		if (d == 'D' && (v & 0x80000000)) 
        {
			v = 0 - v;
			f |= 8;
		}
        
		i = 0;
        
		do 
        {
			d = (char)(v % r); v /= r;
			if (d > 9) d += (c == 'x') ? 0x27 : 0x07;
			s[i++] = d + '0';
		} 
        while (v && i < sizeof(s));
        
		if (f & 8) 
            s[i++] = '-';
        
		j = i; 
        d = (f & 1) ? '0' : ' ';
        
		while (!(f & 2) && 
               j++ < w) 
            m_Serial.write(d);
        
		do 
            m_Serial.write(s[--i]); 
        while(i);
        
		while (j++ < w) 
          m_Serial.write(' ');
	}
}

void x_Print::m_Print_number(unsigned long n, uint8_t base)
{
    char buf[8 * sizeof(long) + 1]; // Assumes 8-bit chars plus zero byte.
    char *str = &buf[sizeof(buf) - 1];
        
    *str = '\0';
    
    // prevent crash if called with base == 1
    if (base < 2) 
    base = 10;
    
    do 
    {
        char c = n % base;
        n /= base;
      
        *--str = c < 10 ? c + '0' : c + 'A' - 10;
    } while(n);
    
    m_Serial.write(str);
}

void x_Print::m_Print_float(double number, uint8_t digits) 
{         
    if (isnan(number))  f("nan");
    if (isinf(number))  f("inf");
    if (number > 4294967040.0) f ("ovf");  // constant determined empirically
    if (number <-4294967040.0) f ("ovf");  // constant determined empirically
    
    // Handle negative numbers
    if (number < 0.0)
    {
       f("-");
       number = - number;
    }
    
    // Round correctly so that f(1.999, 2) prints as "2.00"
    double rounding = 0.5;

    for (uint8_t i = 0; i < digits; ++i)
    rounding /= 10.0;
    
    number += rounding;
    
    // Extract the integer part of the number and f it
    unsigned long int_part = (unsigned long)number;
    double remainder = number - (double)int_part;
    f(int_part);
    
    // f the decimal point, but only if there are digits beyond
    if (digits > 0)
    {
        f("."); 
    }
    
    // Extract digits from the remainder one at a time
    while (digits-- > 0)
    {
        remainder *= 10.0;
        unsigned int to_print = (unsigned int)(remainder);
        f(to_print);
        remainder -= to_print; 
    }
}

x_Print print(&dbg_serial);

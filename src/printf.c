/**
 * @file    printf.c
 * @brief   Minimal printf implementation over USB CDC
 */

#include "n32h47x_48x.h"
#include <stdarg.h>
#include <string.h>
#include "printf.h"


// External function to transmit over USB
extern void cdc_transmit(uint8_t *buf, uint16_t len);


// Tiny printf implementation
int printf(const char *fmt, ...)
{
    char buf[256];
    va_list args;
    va_start(args, fmt);

    // Very basic format handling
    char *p = buf;
    const char *f = fmt;
    
    while (*f && (p - buf) < (int)(sizeof(buf) - 32))
    {
        if (*f == '%')
        {
            f++;
            switch (*f)
            {
                case 's':  // string
                {
                    char *s = va_arg(args, char*);
                    while (*s && (p - buf) < (int)(sizeof(buf) - 1))
                        *p++ = *s++;
                    break;
                }
                case 'x':  // hex
                case 'X':
                {
                    uint32_t val = va_arg(args, uint32_t);
                    char hex[16];
                    int i = 0;
                    do {
                        uint8_t n = val & 0xF;
                        hex[i++] = (n < 10) ? ('0' + n) : ('A' + n - 10);
                        val >>= 4;
                    } while (val && i < 8);
                    while (i > 0)
                        *p++ = hex[--i];
                    break;
                }
                case 'd':  // decimal
                {
                    int32_t val = va_arg(args, int32_t);
                    if (val < 0) { *p++ = '-'; val = -val; }
                    char dec[16];
                    int i = 0;
                    do {
                        dec[i++] = '0' + (val % 10);
                        val /= 10;
                    } while (val && i < 12);
                    while (i > 0)
                        *p++ = dec[--i];
                    break;
                }
                case 'c':  // char
                    *p++ = (char)va_arg(args, int);
                    break;
                case 'l':  // long (ignore, just use 32-bit)
                    f++;     // skip 'l'
                    if (*f == 'x' || *f == 'X')
                    {
                        // Handle %lx like %x
                        uint32_t val = va_arg(args, uint32_t);
                        char hex[16];
                        int i = 0;
                        do {
                            uint8_t n = val & 0xF;
                            hex[i++] = (n < 10) ? ('0' + n) : ('A' + n - 10);
                            val >>= 4;
                        } while (val && i < 8);
                        while (i > 0)
                            *p++ = hex[--i];
                    }
                    break;
                default:
                    *p++ = *f;
                    break;
            }
        }
        else
        {
            *p++ = *f;
        }
        f++;
    }
    *p = '\0';
    va_end(args);

    cdc_transmit((uint8_t *)buf, p - buf);
    return (int)(p - buf);
}


void printf_init(void)
{
    // Nothing needed; printf uses CDC which initializes separately
}

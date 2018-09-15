#ifndef B_PRINTF_H
# define B_PRINTF_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

int             b_printf(const char *format, ...);
int             parse(const char *format, va_list arg_list);
char            spec_check(const char *format, int *ptr);
int             dispatch(va_list arg_list, char specifier);
void            putnbr_base(unsigned long nbr, int base, int *chars);
void            put_integer(va_list arg_list, int *chars);
void            put_char(va_list arg_list, int *chars);
void            put_string(va_list arg_list, int *chars);
void            put_uint(va_list arg_list, int *chars);
void            put_oct(va_list arg_list, int *chars);
void            put_hex(va_list arg_list, int *chars);
void            put_ptr(va_list arg_list, int *chars);
#endif

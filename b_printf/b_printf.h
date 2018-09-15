#ifndef B_PRINTF_H
# define B_PRINTF_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

# define FLAGS "scdipoux"
# define HEX "0123456789abcdef"
# define DEC "0123456789"

int     put_char(va_list arg_list);
int     put_str(va_list arg_list);
void    skip_whitespaces(const char *format, int *ptr);
char    spec_check(const char *format, int *ptr);
int     get_number_len(unsigned long number, int base);
int     putnbr_base(unsigned long number, int base);
int     dispatch(char specifier, va_list arg_list);
int     b_printf(const char *format, ...);
int     parse(const char *format, va_list arg_list);

unsigned int    exponent(unsigned int number, int _exponent);
int             print_dec(unsigned long number, int number_len, int base);    
char            *itoa_base(unsigned long number, int base);
# endif

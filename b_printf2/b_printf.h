#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#define FLAGS "csdiupox"
#define NUM "0123456789abcdef"

void         putnbr_base(unsigned long nbr, int base, int *p);
int         pull_nbr(va_list arg_list, int base);
int         put_char(va_list arg_list);
int         put_string(va_list arg_list);
int         ft_strlen(char *str);
int         dispatch(char specifier, va_list arg_list);
void        ft_putchar(char c);
void        ft_putstr(char *str);
char        spec_check(const char *format, int *ptr);
int         b_printf(const char *format, ...);
int         parse(const char *format, va_list arg_list);

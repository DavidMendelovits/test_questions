#include "b_printf.h"

#define NUM "0123456789abcdef"

void            put_char(va_list arg_list, int *chars)
{
    char            print;

    print = (char)va_arg(arg_list, int);
    ft_putchar(print);
    *chars += 1;
}

void            put_string(va_list arg_list, int *chars)
{
    char            *print;
    int             print_len;
    
    print = va_arg(arg_list, char*);
    print_len = ft_strlen(print);
    write(1, print, print_len);
    *chars += print_len;
}

void            put_integer(va_list arg_list, int *chars)
{
    int             _int;
    
    _int = va_arg(arg_list, int);
    putnbr_base((unsigned long)_int, 10, chars);
}

void            put_uint(va_list arg_list, int *chars)
{
    unsigned int    _uint;

    _uint = va_arg(arg_list, unsigned int);
    putnbr_base((unsigned long)_uint, 10, chars);
}

void            put_octal(va_list arg_list, int *chars)
{
    int             _oct;

    _oct = va_arg(arg_list, int);
    putnbr_base((unsigned long)_oct, 8, chars);
}

void            put_hex(va_list arg_list, int *chars)
{
    unsigned int    _hex;

    _hex = va_arg(arg_list, unsigned int);
    putnbr_base((unsigned long)_hex, 16, chars);
}

void            put_ptr(va_list arg_list, int *chars)
{
    unsigned long   _ptr;

    _ptr = va_arg(arg_list, unsigned long);
    write(1, "0x", 2);
    *chars += 2;
    putnbr_base(_ptr, 16, chars);
}

void            putnbr_base(unsigned long nbr, int base, int *chars)
{
    if (nbr >= base)
    {
        putnbr_base(nbr / base, base, chars);
    }
    if (nbr > base && nbr % base > base)
    {
        ft_putchar(NUM[nbr % base - 1]);
        *chars += 1;
    }
    else
    {
        ft_putchar(NUM[nbr % base]);
        *chars += 1;
    }
}

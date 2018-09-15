#include "b_printf.h"
#define SPECS "scpdioux"
#define NUM "0123456789abcdef"

static int      ft_strlen(char *str)
{
    int             i;

    i = 0;
    while (str[i])
    {
        i += 1;
    }
    return (i);
}

static void            ft_putchar(char c)
{
    write(1, &c, 1);
}

static void            ft_putstr(char *str)
{
    int                 i;

    i = 0;
    while (str[i])
    {
        ft_putchar(str[i]);
        i += 1;
    }
}

void            putnbr_base(unsigned long nbr, int base, int *chars)
{
    if (nbr >= base)
    {
        putnbr_base(nbr / base, base, chars);
    }
    if (nbr > base && nbr % base > 10)
    {
        ft_putchar(NUM[nbr % base]);
        *chars += 1;
    }
    else
    {
        ft_putchar(NUM[nbr % base]);
        *chars += 1;
    }
}

void            put_integer(va_list arg_list, int *chars)
{
    int             _int;

    _int = va_arg(arg_list, int);
    putnbr_base(_int, 10, chars);
}

void            put_char(va_list arg_list, int *chars)
{
    char            print;

    print = (char)va_arg(arg_list, int);
    ft_putchar(print);
}

void            put_string(va_list arg_list, int *chars)
{
    char            *print;

    print = va_arg(arg_list, char*);
    ft_putstr(print);
}

void            put_uint(va_list arg_list, int *chars)
{
    unsigned int    _uint;

    _uint = va_arg(arg_list, unsigned int);
    putnbr_base(_uint, 10, chars);
}

void            put_oct(va_list arg_list, int *chars)
{
    int             _oct;

    _oct = va_arg(arg_list, int);
    putnbr_base(_oct, 8, chars);
}

void            put_hex(va_list arg_list, int *chars)
{
    unsigned int    _hex;

    _hex = va_arg(arg_list, unsigned int);
    putnbr_base(_hex, 16, chars);
}

void            put_ptr(va_list arg_list, int *chars)
{
    unsigned long   _ptr;

    _ptr = va_arg(arg_list, unsigned long);
    write(1, "0x", 2);
    *chars += 2;
    putnbr_base(_ptr, 16, chars);
}

int             dispatch(va_list arg_list, char spec)
{
    int             printed_chars;

    printed_chars = 0;
    if (spec == 'i' || spec == 'd')
    {
        put_integer(arg_list, &printed_chars);
    }
    else if (spec == 'c')
    {
        put_char(arg_list, &printed_chars);
    }
    else if (spec == 's')
    {
        put_string(arg_list, &printed_chars);
    }
    else if (spec == 'u')
    {
        put_uint(arg_list, &printed_chars);
    }
    else if (spec == 'o')
    {
        put_oct(arg_list, &printed_chars);
    }
    else if (spec == 'x')
    {
        put_hex(arg_list, &printed_chars);
    }
    else if (spec == 'p')
    {
        put_ptr(arg_list, &printed_chars);
    }
    return (printed_chars);
}

char            spec_check(const char *format, int *ptr)
{
    int         i;

    i = 0;
    *ptr += 1;
    if (format[*ptr])
    {
        while (i < 8)
        {
            if (SPECS[i] == format[*ptr])
            {
                *ptr += 1;
                return (SPECS[i]);
            }
            i += 1;
        }
    }
    return ('\0');
}

int             parse(const char *format, va_list arg_list)
{
    int         i;
    char        specifier;
    int         printed_chars;

    i = 0;
    printed_chars = 0;
    while (format[i])
    {
        if (format[i] == '%')
        {
            specifier = spec_check(format, &i);
            if (specifier)
            {
                printed_chars += dispatch(arg_list, specifier);
            }
            else
            {
                write(2, "error\n", 6);
            }
        }
        else
        {
            write(1, &format[i], 1);
            i += 1;
            printed_chars += 1;
        }
    }
    return (printed_chars);
}

int             b_printf(const char *format, ...)
{
    int             printed_chars;
    va_list         arg_list;

    va_start(arg_list, format);
    printed_chars = parse(format, arg_list);
    return (printed_chars);
}

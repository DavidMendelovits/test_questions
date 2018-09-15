#include "b_printf.h"

void        ft_putchar(char c)
{
    write(1, &c, 1);
}

int         ft_strlen(char *str)
{
    int         i;

    i = 0;
    while (str[i])
    {
        i += 1;
    }
    return (i);
}

void        ft_putstr(char *str)
{
    int         i;

    i = 0;
    while (str[i])
    {
        ft_putchar(str[i]);
        i += 1;
    }
}

int        put_string(va_list arg_list)
{
    char        *print;

    print = (char*)va_arg(arg_list, char*);
    if (print)
    {
        ft_putstr(print);
        return (ft_strlen(print));
    }
    return (0);
}

int        put_char(va_list arg_list)
{
    char        print;

    print = (char)va_arg(arg_list, int);
    if (print)
    {
        ft_putchar(print);
        return (1);
    }
    return (0);
}

int         pull_nbr(va_list arg_list, int base)
{
    unsigned long               nbr;
    int                         printed_chars;

    printed_chars = 0;
    nbr = va_arg(arg_list, unsigned long);
    putnbr_base(nbr, base, &printed_chars);
    return (printed_chars);
}

void         putnbr_base(unsigned long nbr, int base, int *p)
{
    if (nbr >= base)
    {
        putnbr_base(nbr / (unsigned long)base, base, p);
    }
    unsigned long mod = nbr % base;
 //  printf("\n%lu\n", mod);
    if (nbr > base && nbr % base >= 10)
    {
    //    printf("\n%lu\n", nbr);
        if (nbr % base == 10)
        {
            ft_putchar('a');
        }
        else if (nbr % base == 11)
        {
            ft_putchar('b');
        }
        else if (nbr % base == 12)
        {
            ft_putchar('c');
        }
        else if (nbr % base == 13)
        {
            ft_putchar('d');
        }
        else if (nbr % base == 14)
        {
            ft_putchar('e');
        }
        else if (nbr % base == 15)
        {
            ft_putchar('f');
        }
        *p += 1;
    }
    else if (nbr < base)
    {
        ft_putchar(NUM[nbr]);
        *p += 1;
    }
    else
    {
        ft_putchar(nbr % base + '0');
        *p += 1;
    }
}

int         dispatch(char specifier, va_list arg_list)
{
    int         printed_chars;

    printed_chars = 0;
    if (specifier == 'c')
    {
        printed_chars += put_char(arg_list);
    }
    else if (specifier == 's')
    {
        printed_chars += put_string(arg_list);
    }
    else if (specifier == 'd' || specifier == 'i')
    {
        printed_chars += pull_nbr(arg_list, 10);
    }
    else if (specifier == 'u')
    {
        printed_chars += pull_nbr(arg_list, 10);
    }
    else if (specifier == 'o')
    {
        printed_chars += pull_nbr(arg_list, 8);
    }
    else if (specifier == 'x')
    {
        printed_chars += pull_nbr(arg_list, 16);
    }
    else if (specifier == 'p')
    {
        ft_putstr("0x");
        printed_chars += 2;
        printed_chars += pull_nbr(arg_list, 16);
    }
    return (printed_chars);
}

char        spec_check(const char *format, int *ptr)
{
    char        spec;
    int         i;
    
    *ptr += 1;
    i = ft_strlen(FLAGS) - 1;
    if (format[*ptr])
    {
        while (i >= 0)
        {
            if (format[*ptr] == FLAGS[i])
            {
                *ptr += 1;
                return (FLAGS[i]);
            }
            i -= 1;
        }
    }
    return ('\0');
}

int         parse(const char *format, va_list arg_list)
{
    int         ptr;
    char        specifier;
    int         printed_chars;

    ptr = 0;
    printed_chars = 0;
    while (format[ptr])
    {
        if (format[ptr] == '%')
        {
            specifier = spec_check(format, &ptr);
            if (specifier)
                printed_chars += dispatch(specifier, arg_list);
            else
            {
                write(2, "Error\n", 6);
                return (printed_chars);
            }
        }
        else
        {
            ft_putchar(format[ptr]);
            ptr += 1;
            printed_chars += 1;
        }
    }
    return (printed_chars);
}

int         b_printf(const char *format, ...)
{
    va_list     arg_list;
    int         printed_chars;

    va_start(arg_list, format);
    printed_chars = parse(format, arg_list);
    return (printed_chars);
}

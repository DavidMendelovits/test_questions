#include "b_printf.h"


int        put_char(va_list arg_list)
{
    char            c;

    c = (char)va_arg(arg_list, int);
    if (c)
        write(1, &c, 1);
    else
        return (0);
    return (1);
}

static void        ft_putchar(char c)
{
    write(1, &c, 1);
}

int        put_str(va_list arg_list)
{
    int             i;
    char            *str;

    str = va_arg(arg_list, char*);
    if (str)
    {
        i = 0;
        while (str[i])
        {
            write(1, &str[i], 1);
            i += 1;
        }
        return (i);
    }
    else
    {
        return (0);
    }
}

int     get_number_len(unsigned long number, int base)
{
    int             len;

    len = 0;
    while (number)
    {
        number /= base;
        len += 1;
    }
    return (len);
}

unsigned int    exponent(unsigned int number, int _exponent)
{
    printf("function -> exponent\n");
    unsigned int         ret;

    ret = number;
    while (--_exponent)
    {
        ret *= number;
        printf("%d\n", ret);
    }
    return (ret);
}

char    *itoa_base(unsigned long number, int base)
{
    char                *print;
    int                  num_len;
    unsigned int         div;

    num_len = get_number_len(number, base);
    printf("num_len: %d\n", num_len);
    div = exponent(base, num_len - 1);
    printf("div: %u\n", div);
    return ("placeholder\n");
}

int     print_hex(unsigned long number, int number_len, int base)
{
    int         div;
    
    return (1);
}

int     print_dec(unsigned long number, int number_len, int base)
{
    unsigned int        div;
    char                *num;
    char                print;

    num = malloc(sizeof(*num) * (number_len + 1));
    div = exponent(base, number_len - 1);
    while (div)
    {
        print = number % div + '0';
        ft_putchar(print);
        div /= base;
    }
    return (1);
}

int     putnbr_base(unsigned long number, int base)
{
    int             number_len;
    int             printed_chars;

    printed_chars = 0;
    number_len = get_number_len(number, base);
    if (base == 16)
    {
        printed_chars += print_hex(number, number_len, base);
    }
    return (1);
}

void         skip_whitespaces(const char *format, int *ptr)
{
    while (format[*ptr] == ' ')
    {
        *ptr += 1;
    }
}

char        spec_check(const char *format, int *ptr)
{
    int             i;

    i = 0;
    *ptr += 1;
    if (format[*ptr] == ' ')
    {
         skip_whitespaces(format, ptr);
    }
    while (FLAGS[i])
    {
        if (format[*ptr] == FLAGS[i])
        {
            return (FLAGS[i]);
        }
        i += 1;
    }
    return ('\0');
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
        printed_chars += put_str(arg_list);
    }
    return (printed_chars);
}

int         parse(const char *format, va_list arg_list)
{
    int             i;
    char            specifier;
    int             printed_chars;

    i = 0;
    printed_chars = 0;
    while (format[i])
    {
        if (format[i] == '%')
        {
            specifier = spec_check(format, &i);
            i += 1;
            if (specifier)
            {
                dispatch(specifier, arg_list);
            }
        }
        else
        {
            write(1, &format[i], 1);
            i += 1;
            printed_chars += 1;
        }
    }
}

int         b_printf(const char *format, ...)
{
    va_list         arg_list;
    int             printed_chars;

    va_start(arg_list, format);
    printed_chars = 0;
    printed_chars = parse(format, arg_list);
    va_end(arg_list);
    return (printed_chars);
}

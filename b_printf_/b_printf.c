#include "b_printf.h"

#define ERRORCODE "Error -> Invalid Syntax..."
#define FLAGS "scpdiouxp"

int             ft_strlen(char *str)
{
    int             i;

    i = 0;
    while (str[i])
    {
        i += 1;
    }
    return (i);
}

void            ft_putchar(char c)
{
    write(1, &c, 1);
}

void            ft_putstr(char *str)
{
    int             i;

    i = 0;
    while (str[i])
    {
        ft_putchar(str[i]);
        i += 1;
    }
}


char            spec_check(const char *format, int *ptr)
{
    int     i;

    i = ft_strlen(FLAGS) - 1;
    *ptr += 1;
    if (format[*ptr])
    {
        while (i >= 0)
        {
            if (FLAGS[i] == format[*ptr])
            {
                *ptr += 1;
                return (FLAGS[i]);
            }
            i -= 1;
        }
    }
    return ('\0');
}

int             dispatch(char specifier, va_list arg_list)
{
    int         printed_characters;

    printed_characters = 0;
    if (specifier == 'c')
    {
        put_char(arg_list, &printed_characters);
    }
    else if (specifier == 's')
    {
        put_string(arg_list, &printed_characters);
    }
    else if (specifier == 'i' || specifier == 'd')
    {
        put_integer(arg_list, &printed_characters);
    }
    else if (specifier == 'u')
    {
        put_uint(arg_list, &printed_characters);
    }
    else if (specifier == 'o')
    {
        put_octal(arg_list, &printed_characters);
    }
    else if (specifier == 'x')
    {
        put_hex(arg_list, &printed_characters);
    }
    else if (specifier == 'p')
    {
        put_ptr(arg_list, &printed_characters);
    }
    return (printed_characters);
}

int             parse(const char *format, va_list arg_list)
{
    int             printed_characters;
    int             ptr;
    char            specifier;

    ptr = 0;
    printed_characters = 0;
    while (format[ptr])
    {
        if (format[ptr] == '%')
        {
            specifier = spec_check(format, &ptr);
            if (specifier)
            {
                printed_characters += dispatch(specifier, arg_list);
            }
            else
            {
                write(2, ERRORCODE, ft_strlen(ERRORCODE));
                ft_putchar('\n');
            }
        }
        else
        {
            ft_putchar(format[ptr]);
            ptr += 1;
            printed_characters += 1;
        }
    }
    return (printed_characters);
}

int             b_printf(const char *format, ...)
{
    int         printed_characters;
    va_list     arg_list;

    va_start(arg_list, format);
    printed_characters = parse(format, arg_list);
    return (printed_characters);
}

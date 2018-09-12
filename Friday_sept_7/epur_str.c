#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int     is_space(char c)
{
    if (c == ' ' || c == '\t')
    {
        return (1);
    }
    return (0);
}

int     skip_whitespace(char *str, int sp)
{
    while (str[sp] == ' ' || str[sp] == '\t')
    {
        sp += 1;
    }
    return (sp);
}

char    *ft_strjoin_range(char *s1, char *s2, int s2_ptr, int s2_end)
{
    char        *new_str;
    int         new_str_len;
    int         s1_ptr;
    int         ptr;
    static int  s1_exists = 0;

    new_str_len = 0;
    if (s1)
    {
        new_str_len += strlen(s1) + 1; // + 1 for space
        s1_exists = 1;
    }
    new_str_len += s2_end - s2_ptr + 1;
    new_str = malloc(sizeof(sizeof(char) * (new_str_len + 1)));
    s1_ptr = 0;
    ptr = 0;
    while (s1_exists && s1[ptr])
    {
        new_str[ptr] = s1[s1_ptr];
        ptr += 1;
        s1_ptr += 1;
    }
    if (s1_exists)
        new_str[ptr++] = ' ';
    while (s2_ptr <= s2_end)
    {
        new_str[ptr] = s2[s2_ptr];
        ptr += 1;
        s2_ptr += 1;
    }
    new_str[ptr] = '\0';
    free(s1);
    return (new_str);
}

char    *epur_str(char *str)
{
    int     sp;
    int     word_begin;
    char    *condensed_string;

    sp = 0;
    condensed_string = malloc(sizeof(condensed_string));
    condensed_string = NULL;
    while (str[sp])
    {
        if (is_space(str[sp]))
        {
            sp = skip_whitespace(str, sp);
        }
        else
        {
            word_begin = sp;
            while (!is_space(str[sp]) && str[sp])
            {
                sp += 1;
            }
            condensed_string = ft_strjoin_range(condensed_string, str, word_begin, sp - 1);
        }
    }
    return (condensed_string);
}

void    print_condensed_str(char *str)
{
    char    *string;

    string = epur_str(str);
    printf("condensed str:\n%s\n", string);
}

int     main(int argc, char **argv)
{
    if (argc == 2)
    {
        print_condensed_str(argv[1]);
    }
    return (0);
}

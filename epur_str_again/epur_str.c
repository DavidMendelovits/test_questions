#include <stdlib.h>
#include <stdio.h>


int     count_words(char *str)
{
    int         i;
    int         count;

    i = 0;
    count = 0;
    while (str[i])
    {
        if (str[i] != ' ' && str[i] != '\t')
        {
            count += 1;
            while (str[i] && str[i] != ' ' && str[i] != '\t')
            {
                i += 1;
            }
        }
        else
        {
            i += 1;
        }
    }
    return (count);
}

char    *strdup_range(char *str, int begin, int end)
{
    int         s_ptr;
    char        *duplicate;
    int         d_ptr;

    duplicate = malloc(sizeof(duplicate) * (end - begin + 2));
    s_ptr = begin;
    d_ptr = 0;
    while (s_ptr <= end)
    {
        duplicate[d_ptr] = str[s_ptr];
        d_ptr += 1;
        s_ptr += 1;
    }
    duplicate[d_ptr] = '\0';
    return (duplicate);
}

char    **str_split(char *str)
{
    int         str_ptr;
    char        **strings;
    int         strings_ptr;
    int         word_count;
    int         word_begin;

    word_count = count_words(str);
    printf("word_count = %d\n", word_count);
    strings = malloc(sizeof(strings) * (word_count + 1));
    str_ptr = 0;
    strings_ptr = 0;
    while (str[str_ptr])
    {
        if (str[str_ptr] != '\t' && str[str_ptr] != ' ')
        {
            word_begin = str_ptr;
            while(str[str_ptr] != '\t' && str[str_ptr] != ' ' && str[str_ptr])
            {
                str_ptr += 1;
            }
            strings[strings_ptr] = strdup_range(str, word_begin, str_ptr - 1);
            printf("\nstrings[%d] = %s\n", strings_ptr, strings[strings_ptr]);
            strings_ptr += 1;
        }
        else
        {
            str_ptr += 1;
        }
    }
    strings[strings_ptr] = NULL;
    return (strings);
}

void    print_strings(char **strings)
{
    int         i;

    i = 0;
    while (strings[i])
    {
        printf("%s", strings[i]);
        if (strings[i + 1])
        {
            printf(" ");
        }
        i += 1;
    }
}

void    epur_str(char *str)
{
    char        **strings;

    strings = str_split(str);
    print_strings(strings);
}

int     main(int argc, char **argv)
{
    if (argc == 2)
    {
        epur_str(argv[1]);
    }
    return (0);
}

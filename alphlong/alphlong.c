#include <unistd.h>
#include <stdlib.h>

typedef struct      s_sort
{
    int         **sorted_words; // points to position of words in order of length
    int         min_len;
    int         max_len;
}                   t_sort;


void    ft_putchar(char c)
{
    write(1, &c, 1);
}

void    ft_putstr(char *str)
{
    int     i;

    i = 0;
    while (str[i])
    {
        ft_putchar(str[i]);
    }
}

void    find_range(char *str, t_sort *sort)
{
    int     i;
    int     word_len;

    i = 0;
    (*sort).min_len = 0;
    (*sort).max_len = 1;
    while (str[i])
    {
        if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
        {
            word_len = 0;
            while (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
            { 
                i++;
                word_len++;
            }
            if (word_len >= (*sort).max_len)
            {
                (*sort).max_len = word_len;
            }
            else if (word_len <= (*sort).min_len)
            {
                (*sort).min_len = word_len;
            }
        }
    }
}

void    allocate_sorted_words(t_sort *sort)
{
    int     range;
    int     i;
    int     index;

    range = (*sort).max_len - (*sort).min_len;
    (*sort).sorted_words = malloc(sizeof((*sort).sorted_words) * ((range) + 1));
    i = (*sort).min_len;
    index = 0;
    while (i <= (*sort).max_len)
    {
        (*sort).sorted_words[index] = malloc(sizeof(int) * (i + 1));
        i++;
        index++;
    }
}

void    alphlong(char *str)
{
    int         i;
    t_sort      sort;
    
    i = 0;
    find_range(str, &sort);
    allocate_sorted_words(&sort);
    find_words(str, &sort);

}

int     main(int argc, char **argv)
{
    if (argc == 2)
    {
        alphlong(argv[1]);
    }
    ft_putstr("\n");
    return (0);
}

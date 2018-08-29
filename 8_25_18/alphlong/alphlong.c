#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

typedef struct      s_sort
{
    int     **word_pointers;
    int     min_len;
    int     max_len;
    int     word_count;
}                   t_sort;

typedef struct      s_print
{
    int     i;
    int     j;
}                   t_print;

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
        i++;
    }
}

int    ft_strlen(char *str)
{
    int     i;

    i = 0;
    while (str[i])
    {
        i++;
    }
    return (i);
}

void    get_range(t_sort *sort, char *str)
{
    int     i;
    int     word_len;
    int     str_len;

    i = 0;
    (*sort).min_len = 0;
    (*sort).max_len = 0;
    (*sort).word_count = 0;
    str_len = ft_strlen(str);
    while (i < str_len)
    {
        if (str[i] != '\n' && str[i] != ' ' && str[i] != '\t' && str[i] != '\0')
        {
            word_len = 0;
            (*sort).word_count += 1;
            while (str[i] != '\n' && str[i] != ' ' && str[i] != '\t' && str[i] != '\0')
            {
                word_len++;
                i++;
            }
            if ((*sort).min_len == 0 && (*sort).max_len == 0)
            {
                (*sort).max_len = word_len;
                (*sort).min_len = word_len;
            }
            if (word_len > (*sort).max_len)
            {
                (*sort).max_len = word_len; 
            }
            else if (word_len < (*sort).min_len)
            {
                (*sort).min_len = word_len;
            }
        }
        i++;
    }
}

void    allocate_word_pointers(t_sort *sort, char *str)
{
    int     i;
    int     j;
    int     range;

    range = (*sort).max_len - (*sort).min_len + 1;
    (*sort).word_pointers = malloc(sizeof(int *) * range);
    i = 0;
    while (i < range)
    {
        (*sort).word_pointers[i] = malloc(sizeof(int) * (*sort).word_count);
        j = 0;
        while (j < (*sort).word_count)
        {
            (*sort).word_pointers[i][j] = ('\0');
            j++;
        }
        i++;
    }
}

int     place_word_pointer(t_sort *sort, int *i, char *str)
{
    int     sort_index;
    int     word_len;

    word_len = 0;
    while (str[*i] != '\n' && str[*i] != ' ' && str[*i] != '\t' && str[*i] != '\0')
    {
        word_len++;
        (*i)++;
    }
    sort_index = word_len - (*sort).min_len;
    return (sort_index);
}

int     get_word_index(t_sort *sort, int sort_index)
{
    int             word_index;

    word_index = 0;
    while (word_index < (*sort).word_count)
    {
        if ((*sort).word_pointers[sort_index][word_index] == '\0')
        {
            break ;
        }
        word_index += 1;
    }
    return (word_index);
}

void    populate_int_arrays(t_sort *sort, char *str)
{
    int             i;
    int             sort_index;
    static int      word_index = 0;
    int             word_start;
    int             str_len;

    i = 0;
    str_len = ft_strlen(str);
    while (i < str_len)
    {
        if (str[i] != '\n' && str[i] != ' ' && str[i] != '\t')
        {
            word_start = i;
            sort_index = place_word_pointer(sort, &i, str);
            word_index = get_word_index(sort, sort_index);
            (*sort).word_pointers[sort_index][word_index] = word_start;
            printf("word_ptr: %d\n", word_start);
            printf("place at word_pointers[%d][%d]: %d\n", sort_index, word_index, (*sort).word_pointers[sort_index][word_index]);
        }
        else
        {
            i++;
        }
    }
}

void    print_word(t_sort sort, char *str, t_print dub_ptr_index)
{
    int     word_ptr;
    
    word_ptr = sort.word_pointers[dub_ptr_index.i][dub_ptr_index.j];
    while (str[word_ptr] != '\n' && str[word_ptr] != ' ' && str[word_ptr] != '\t' && str[word_ptr] != '\0')
    {
        ft_putchar(str[word_ptr]);
        word_ptr += 1;
    }
    ft_putchar(' ');
}

void    print_sorted_words(t_sort sort, char *str)
{
    t_print     dub_ptr;
    int         range;

    dub_ptr.i = 0;
    range = sort.max_len - sort.min_len + 1;
    while (dub_ptr.i < range)
    {
        dub_ptr.j = 0;
        printf("%d ", sort.word_pointers[dub_ptr.i][dub_ptr.j]);
        if (sort.word_pointers[dub_ptr.i][dub_ptr.j] == 0)
        {
            print_word(sort, str, dub_ptr);
        }
        while (sort.word_pointers[dub_ptr.i][dub_ptr.j] != '\0')
        {
            print_word(sort, str, dub_ptr);
            dub_ptr.j += 1;
        }
        dub_ptr.i += 1;
        ft_putstr("\n");
    }
}

void    alphlong(char *str)
{
    t_sort      sort;
    int         i;

    get_range(&sort, str);
    allocate_word_pointers(&sort, str);
    populate_int_arrays(&sort, str);
    print_sorted_words(sort, str);
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

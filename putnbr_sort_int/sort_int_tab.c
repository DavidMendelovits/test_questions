#include "putnbr.c"
#include <stdio.h>
#include <stdlib.h>

void    ft_swap_int(int *a, int *b)
{
    int     tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;
}

void    sort_int_tab(int *array, int tab)
{
    int         sorted;
    int         ap;

    sorted = 0;
    while (!sorted)
    {
        sorted = 1;
        ap = tab - 1;
        while (ap > 0)
        {
            if (array[ap] < array[ap - 1])
            {
                sorted = 0;
                ft_swap_int(&array[ap], &array[ap - 1]);
            }
            ap -= 1;
        }
    }
}

int     main(void)
{
    int     array[] = { 1, 34, 2, 6, 8, 2 };
    int     array_len = 6;
    
    sort_int_tab(array, array_len);

    int     i = 0;
    while (i < array_len)
    {
        ft_putnbr(array[i]);
        printf("\n");
        i += 1;
    }
    return (0);
}

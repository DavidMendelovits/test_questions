void    ft_swap(int *n_1, int *n_2)
{
    int     tmp;

    tmp = *n_1;
    *n_1 = *n_2;
    *n_2 = tmp;
}

int     check_sort(int *tab, unsigned int size)
{
    while (size > 0)
    {
        if (tab[size] < tab[size - 1])
            return (0);
        size--;
    }
    return (1);
}

void    sort_int_tab(int *tab, unsigned int size)
{
    unsigned int    i;
    int             sorted;

    i = size - 1;
    sorted = 0;
    while (i > 0 && !sorted)
    {
        if (tab[i] < tab[i - 1])
        {
            ft_swap(&tab[i], &tab[i - 1]);
        }
        i--;
        if (check_sort(tab, size))
        {
            sorted = 1;
        }
    }
    if (!sorted)
    {
        sort_int_tab(tab, size);
    }
}

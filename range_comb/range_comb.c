#include <stdlib.h>
#include <stdio.h>

int     factorial(int n)
{
    int     ret;

    ret = 0;
    while (n > 0)
    {
        ret += (n * (n - 1));
        n--;
    }
    return (ret);
}

void    set_first_combination(int **combination, int n)
{
    int     i;

    i = 0;
    printf("{ ");
    while (i <= n)
    {
        *combination[i] = i;
        printf(" {%d} ", *combination[i]);
        i++;
    }
    printf(" } ");
}

int     find_number(int *i, int index, int **comb)
{
    static int      ptr = 0;
    int             num;

    num = (*i);

    if (comb[ptr][index] == i)
    {

    }
}

void    write_combination(int ***combination, int n, int index)
{
    int     i;

    i = 0;
    while (i <= n)
    {
        if (!find_number(&i, index, *combination))
        {
             return ;
        }
        *combination[i] = i;

    }
}

int     **range_comb(int n)
{
    int        **permutations;
    int         i;

    if (n <= 0)
    {
        return (NULL);
    }
    permutations = malloc(sizeof(permutations) * (factorial(n - 1)));
    i = 0;
    set_first_combination(&permutations[i], n - 1);
    while (i < factorial(n - 1))
    {
        permutations[i] = malloc(sizeof(int) * n);
        write_combination(&permutations, n - 1, i);
    }
    return (permutations);
}

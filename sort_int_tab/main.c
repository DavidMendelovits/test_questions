#include <stdio.h>

void    sort_int_tab(int *tab, unsigned int size);
int     main(void)
{
    int     array[] = { 2, 5, 8, 6 };
    
    sort_int_tab(array, 4);
    for (int i = 0; i < 4; i++)
    {
        printf("%d ", array[i]);
    }
    return (0);
}
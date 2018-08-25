#include <stdio.h>

void    sort_int_tab(int *tab, unsigned int size);
int     main(void)
{
    int     array[] = { 2, 5, 8, 6, 90, 98, 76, 87, 93 };
    
    sort_int_tab(array, 9);
    for (int i = 0; i < 9; i++)
    {
        printf("%d ", array[i]);
    }
    return (0);
}

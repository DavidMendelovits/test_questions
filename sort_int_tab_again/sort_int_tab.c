#include <stdio.h>

void    ft_swap(int *a, int *b)
{
    int     tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;
}

void    print_array(int *array, int len)
{
    int     i;

    i = 0;
    while (i < len)
    {
        printf("%d ", array[i]);
        i += 1;
    }

}
void    sort_int_tab(int *array, int len)
{
    int     array_ptr;
    int     sorted;

    array_ptr = len - 1;
    sorted = 0;
    while (sorted != 1)
    {
        sorted = 1;
        while (array_ptr > 0)
        {
            if (array[array_ptr] < array[array_ptr - 1])
            {
		printf("\nSwap -> %d - %d ", array[array_ptr], array[array_ptr - 1]);
                ft_swap(&array[array_ptr], &array[array_ptr - 1]);
                sorted = 0;
		printf("-> %d - %d\n", array[array_ptr], array[array_ptr - 1]);
            }
            array_ptr -= 1;
        }
        array_ptr = len - 1;
    }
    print_array(array, len);
}

int     main(void)
{
    int     array[7] = { 3, 5, 7, 8, 33, 23, 24 };
    
  //  print_array(array, 7);
    sort_int_tab(array, 7);
}

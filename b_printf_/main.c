#include "b_printf.h"

int         main()
{
    b_printf("%s %c...%c...%c\n", "testing", '1', '2', '3');
    printf("%s %c...%c...%c\n", "testing", '1', '2', '3');
    b_printf("%i + %d = %d\n", 12345, 10000, 12345 + 10000);
    printf("%i + %d = %d\n", 12345, 10000, 12345 + 10000);
    b_printf("%u * %u = %u\n", 123456, 100000, (unsigned int)123456 * (unsigned int)100000);
    printf("%u * %u = %u\n", 123456, 100000, (unsigned int)123456 * (unsigned int)100000);
    b_printf("%o\n", 123456);
    printf("%o\n", 123456);
    b_printf("%x\n", 123456);
    printf("%x\n", 123456);
    int *a = malloc(sizeof(int));
    b_printf("%p\n", &a);
    printf("%p\n", &a);
    return (0);
}

#include "b_printf.h"


void        main()
{
//    b_printf("testing... %c... %c... %c...\n", '1', '2', '3');
//    printf("testing... %c... %c... %c...\n", '1', '2', '3');
//    b_printf("%s %s %s\n", "we", "are", "okay");
//    printf("%s %s %s\n", "we", "are", "okay");
//    b_printf("%d + %d = %d\n", 12, 12, 24);
//    printf("%d + %d = %d\n", 12, 12, 24);
//    b_printf("%o * %o = %o\n", 111110, 12, 111110 * 12);
//    b_printf("%o * %o = %o\n", 111110, 12, 111110 * 12);
//    b_printf("hex test: %x\n", 123456);
//    printf("hex test: %x\n", 123456);
    b_printf("hex test: %x\n", 0xefff);
    printf("hex test: %x\n", 0xefff);
    b_printf("hex test: %x\n", 0x12f5);
    printf("hex test: %x\n", 0x12f5);
    b_printf("hex test: %x\n", 65535);
    printf("hex test: %x\n", 65535);
    int     *ptr;
    ptr = malloc(sizeof(int) * 3);
    ptr[0] = 1;
    b_printf("%p\n", &ptr);
    printf("%p\n", &ptr);
    b_printf("%p\n", NULL);
    printf("%p\n", NUL);
}

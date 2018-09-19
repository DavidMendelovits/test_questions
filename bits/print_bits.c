#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void            print_bits(unsigned char octet)
{
    int             shift;

    shift = 7;
    while (shift >= 0)
    {
        if (octet >> shift & 1)
        {
            write(1, "1", 1);
        }
        else
        {
            write (1, "0", 1);
        }
        shift -= 1;
    }
}
/*
int             main(int argc, char **argv)
{
    if (argc == 2)
        print_bits((unsigned char)argv[1][0]);
    printf("\n");
    return (0);
}
*/

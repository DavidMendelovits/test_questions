#include <stdio.h>
#include <stdlib.h>
#include "bits.h"

unsigned char       swap_bits(unsigned char octet)
{
    return (octet >> 4 | octet << 4);
}

int                 main(int argc, char **argv)
{
    if (argc == 2)
    {
        print_bits(argv[1][0]);
        printf("\n");
        print_bits(swap_bits(argv[1][0]));
    }
    return (0);
}

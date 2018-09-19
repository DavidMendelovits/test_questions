#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "bits.h"

unsigned char       reverse_bits(unsigned char octet)
{
    unsigned char           rev;
    int                     shift;
    int                     r_shift;

    r_shift = 7;
    shift = 0;
    rev = 0;
    while (shift < 8)
    {
        if (octet >> shift & 1)
        {
            rev |= 1;
        }
        if (r_shift)
        {
            rev <<= 1;
        }
        r_shift -= 1;
        shift += 1; 
    }
    return (rev);
}


int                 main(int argc, char **argv)
{
    if (argc == 2)
    {
        print_bits((unsigned char)argv[1][0]);
        printf("\n");
        print_bits(reverse_bits((unsigned char)argv[1][0]));
    }
    return (0);
}

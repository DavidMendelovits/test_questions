#include <stdio.h>

unsigned char   reverse_bits(unsigned char octet)
{
    unsigned char ret = 0;
    int           ret_ptr = 0;
    int           octet_ptr = 7;

    while (octet_ptr >= 0)
    {
        ret << ret_ptr | octet >> octet_ptr;
        ret_ptr += 1;
        octet_ptr -= 1;
    }
    return (ret);
}

int             main()
{
    unsigned char   octet = 'A';

    print_bits(reverse_bits(octet));
    return (0);
}

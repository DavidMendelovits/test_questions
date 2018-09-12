#include <stdio.h>
#include <stdlib.h>

unsigned int    get_hcf(unsigned int a, unsigned int b)
{
    unsigned int         hcf;
    unsigned int         div;

    div = 1;
    while (div <= a && div <= b)
    {
        if (a % div == 0 && b % div == 0)
        {
            hcf = div;
            printf("div: %d\n", hcf);
        }
        div += 1;
    }
    return (hcf);
}

unsigned int    lcm(unsigned int a, unsigned int b)
{
    unsigned int         lcm;
    unsigned int         hcf;

    hcf = get_hcf(a, b);
    printf("hcf: %d\n", hcf);
    lcm = (a * b) / hcf;
    return (lcm);
}

int         main(int argc, char **argv)
{
    if (argc == 3)
    {
        printf("lcm: %d\n", lcm((unsigned int)atoi(argv[1]), (unsigned int)atoi(argv[2])));
    }
    return (0);
}

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void        ft_putchar(char c)
{
    write(1, &c, 1);
}

void        ft_putnbr(int nbr)
{
    static int      called = 0;

    printf("putnbr called %d times\n", ++called);
    printf("nbr = %d\n", nbr);
    printf("nbr % 10 = %d\n", nbr % 10);
    if (nbr > 10)
    {
        ft_putnbr(nbr / 10);
    }
    ft_putchar(nbr % 10 + '0');
}

void        ft_putnbr_base(int nbr, int base)
{
    static int      called = 0;

    printf("putnbr_base called %d times\n", ++called);
    if (nbr > base)
    {
        ft_putnbr_base(nbr / base, base);
    }
    if (base > 10 && nbr > 10)
    {
       ft_putchar(nbr% base - 10 + 'A'); 
    }
    else
    {
        ft_putchar(nbr % base + '0');

    }
}

int         main(int argc, char **argv)
{
    int    number = 0xff112;

    ft_putnbr_base(number, 16);
    if (argc == 3)
    {
        ft_putnbr_base(atoi(argv[1]), atoi(argv[2]));
    }
    return (0);
}

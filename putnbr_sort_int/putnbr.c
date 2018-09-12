#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void        ft_putchar(char c)
{
    write(1, &c, 1);
}

int         ft_nbrlen(int nbr)
{
    int     div;
    int     len;

    if (nbr == 0)
    {
        return (1);
    }
    div = 1;
    len = 0;
    while (nbr / div)
    {
        div *= 10;
        len += 1;
    }
    return (len);
}

void        ft_putnbr(int nbr)
{
    int     nbr_len;
    int     power;
    int     tens;

    nbr_len = ft_nbrlen(nbr);
//    printf("nbr_len: %d\n", nbr_len);
    power = 1;
    tens = 0;
    while (tens < nbr_len)
    {
        tens += 1;
        power *= 10;
  //      printf("power: %d\n", power);
    }
    while (tens > 0)
    {
        tens -= 1;
        power /= 10;
        ft_putchar((nbr / power) + '0'); 
        nbr %= power;

    }
}
/*
int         main(int argc, char **argv)
{
    if (argc == 2)
    {
        ft_putnbr(atoi(argv[1]));
        printf("\n%d\n", atoi(argv[1]));
    }
    return (0);
}
*/

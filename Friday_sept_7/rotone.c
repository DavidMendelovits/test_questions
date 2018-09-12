#include <stdio.h>

void    block_cipher(char *str)
{
    int     i;

    i = 0;
    while (str[i])
    {
        if (str[i] >= 'A' && str[i] < 'Z')
        {
            str[i] += 1;
        }
        else if (str[i] == 'Z')
        {
            str[i] = 'A';
        }
        else if (str[i] >= 'a' && str[i] < 'z')
        {
            str[i] += 1;
        }
        else if (str[i] == 'z')
        {
            str[i] = 'a';
        }
        printf("%c", str[i]);
        i += 1;
    }
    printf("\n");
}

int     main(int argc, char **argv)
{
    if (argc == 2)
    {
        block_cipher(argv[1]);
    }
    return (0);
}

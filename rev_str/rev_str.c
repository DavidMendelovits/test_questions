#include <stdio.h>
#include <stdlib.h>


int		ft_strlen(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		i += 1;
	}
	return (i);
}

void		ft_swap(char *a, char *b)
{
	char		tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

char		*rev_str(char *str)
{
	int		i;
	int		j;

	i = 0;
	j = ft_strlen(str) - 1;
	while (i <= j)
	{
		ft_swap(&str[i], &str[j]);
		j -= 1;
		i += 1;
	}
	return (str);
}

int		main(int argc, char **argv)
{
	if (argc == 2)
	{
		printf("reversed string: %s\n", rev_str(argv[1]));
	}
	return (0);
}

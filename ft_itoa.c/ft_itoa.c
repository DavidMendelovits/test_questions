#include <stdlib.h>
#include <stdio.h>

static int	number_len(int number)
{
	printf("function -> number_len: %d\n", number);

	int	div;
	int	len;

	div = 10;
	len = 0;
	while (number / div > 0)
	{
		printf("%d /= %d ->", number, div);
		number /= div;
		div *= 10;
		printf("%d", number);
		len += 1;
		if (!number)
		{
			break ;
		}
	}
	return (len);
}

char		*ft_itoa(int number)
{
	int		div;
	char		*string;
	int		string_ptr;
	int		number_length;

	div = 10;
	number_length = 
	while (number > 0)
	{
		break ;	
	}
	return ("placeholder\n");
}

int		main(int argc, char **argv)
{
	if (argc == 2)
	{
		printf("int to string: %s\n", ft_itoa(atoi(argv[1])));	
	}
	return (0);
}

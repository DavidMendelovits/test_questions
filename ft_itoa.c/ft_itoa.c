#include <stdlib.h>
#include <stdio.h>

typedef struct		s_number
{
	int		length;
	int		is_negative:1;
	int		number;
}			t_number;

static int	number_len(int number)
{
	int		length;
	
	length = 1;
	while (number >= 10)
	{
		number /= 10;
		length += 1;
	}
	return (length);
}

char		*ft_itoa(int number)
{
	int		div;
	char		*string;
	int		number_length;
	int		string_ptr;
	
	number_length = 0;
	if (number < 0)
	{
		number *= -1;
		number_length = 1;
	}
	number_length += number_len(number);
	printf("number: %d\n", number_length);
	return ("placeholder");
}

int		main(int argc, char **argv)
{
	if (argc == 2)
	{
		printf("\nint to string: %s\n", ft_itoa(atoi(argv[1])));	
	}
	return (0);
}

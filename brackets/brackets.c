#include <stdio.h>


void	brackets(char *str)
{
	char	stack[1024];
	int	stack_ptr;
	int	i;
	int	ok;

	i = 0;
	stack_ptr = 0;
	ok = 1;
	while (str[i] != '\0')
	{
		if (str[i] == '(' || str[i] == '[' || str[i] == '{')
		{
			stack[stack_ptr] = str[i];
			stack_ptr += 1;
			ok = 0;
		}
		else if (str[i] == ')' || str[i] == ']' || str[i] == '}')
		{
			if (str[i] == ')')
			{
				if (stack[stack_ptr - 1] != '(')
				{
					printf("\nERROR\n");
					return ;
				}
				stack_ptr -= 1;
			}
			else if (str[i] == ']')
			{
				if (stack[stack_ptr - 1] != '[')
				{
					printf("\nERROR\n");
					return ;
				}
				stack_ptr -= 1;		
			}
			else if (str[i] == '}')
			{
				if (stack[stack_ptr - 1] != '{')
				{
					printf("\n ERROR\n");
					return ;
				}
				stack_ptr -= 1;
			}

		}
		i += 1;
	}
	if (stack_ptr == 0)
	{
		ok = 1;
	}
	if (ok == 1)
	{
		printf("\nok\n");
		return ;
	}
	printf("\nERROR\n");
}

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		brackets(argv[1]);
	}
	printf("\n");
	return (0);
}

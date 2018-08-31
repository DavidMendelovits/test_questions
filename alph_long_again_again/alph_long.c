#include <stdio.h>
#include <stdlib.h>

int	g_word_count;

int	skip_whitespace(char *str)
{
	int 		i;

	i = 0;
	if (str[0] == ' ' || str[i] == '\t')
	{
		while (str[i] == ' ' || str[i] == '\t')
		{
			i += 1;
		}
	}
	return (i);
}

int	ft_strlen(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		i += 1;
	}
	return (i);
}

int	ft_count_words(char *str)
{
	int		i;
	int 		count;
	int		len;

	i = skip_whitespace(str);
	count = 0;
	if (str[i] != '\0')
	{
		count += 1;
	}
	len = ft_strlen(str);
	while (i < len)
	{
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '\0')
		{
			while ((str[i] == ' ' || str[i] == '\t') && str[i] != '\0')
			{
				i += 1;
			}
			if (str[i] != '\0')
			{
				count += 1;
			}
		}
		else
		{
			i += 1;
		}
	}
	printf("\ntesting count_words: %d\n", count);
	return (count);
}

char	*ft_strdup_range(char *str, int begin, int end)
{
	int	range;
	char	*string;
	int	str_ptr;
	int	string_ptr;;

	range = end - begin + 1;
	string = malloc(sizeof(char) * (range + 1));
	str_ptr = begin;
	string_ptr = 0;
	while (str_ptr <= end)
	{
		string[string_ptr] = str[str_ptr];
		str_ptr += 1;
		string_ptr += 1;
	}
	string[string_ptr] = '\0';
	return (string);
}

char	**ft_strsplit(char *str)
{
	int	i;
	char	**strings;
	int	begin;
	int	strings_ptr;

	i = 0;
	g_word_count = ft_count_words(str);
	strings = malloc(sizeof(strings) * (g_word_count + 1));
	strings_ptr = 0;
	printf("\nFunction -> ft_strsplit:\n");
	printf("\nstr = %s\n", str);
	while (str[i] != '\0')
	{
		if (str[i] != ' ' && str[i] != '\t')
		{
			begin = i;
			while (str[i] != ' ' && str[i] != '\t' && str[i] != '\0')
			{
				i += 1;
			}
			strings[strings_ptr] = ft_strdup_range(str, begin, i - 1);
			printf("%s\n", strings[strings_ptr]);
			strings_ptr += 1;
		}
		else
		{
			i += 1;
		}
	}
	return (strings);
}

void	print_strings(char **strings)
{
	int	i;

	i = 0;
	printf("\nFunction -> print_strings:\n");
	while (strings[i] != NULL)
	{
		printf("%s\n", strings[i]);
		i += 1;
	}

}

void	ft_string_swap(char **string1, char **string2)
{
	char	*tmp;

	printf("\nSwap: %s - %s ->", *string1, *string2);
	tmp = *string1;
	*string1 = *string2;
	*string2 = tmp;
	printf("%s - %s\n", *string1, *string2);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
		i += 1;
	}
	return (s1[i] - s2[i]);
}

void	sort_strings(char **strings)
{
	int		strings_ptr;
	int		sorted;

	strings_ptr = g_word_count - 1;
	sorted = 0;
	while (sorted == 0)
	{
		sorted = 1;
		while (strings_ptr > 0)
		{
			if (ft_strlen(strings[strings_ptr]) < ft_strlen(strings[strings_ptr - 1]))
			{
				sorted = 0;
				ft_string_swap(&strings[strings_ptr], &strings[strings_ptr - 1]);
			}
			else if (ft_strlen(strings[strings_ptr]) == ft_strlen(strings[strings_ptr - 1]))
			{
				if (ft_strcmp(strings[strings_ptr], strings[strings_ptr - 1]) < 0)
				{
					sorted = 0;
					ft_string_swap(&strings[strings_ptr], &strings[strings_ptr - 1]);
				}
			}
			strings_ptr -= 1;
		}
		strings_ptr = g_word_count - 1;
	}
}

void	alph_long(char *str)
{
	char 	**strings;

	strings = ft_strsplit(str);
	print_strings(strings);
	sort_strings(strings);
	print_strings(strings);
}

int	main(int argc, char **argv)
{
	printf("\nChecking ft_strdup_range: %s\n", ft_strdup_range("012345678911111", 3, 8));
	if (argc == 2)
	{
		alph_long(argv[1]);
	}
	printf("\n");
	return (0);
}

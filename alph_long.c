#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

int	count_words(char *str)
{
	int		i;
	int		word_count;

	i = 0;
	word_count = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
		{
			word_count += 1;
			while (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i])
			{
				i += 1;
			}
		}
		if (str[i] == '\0')
		{
			break ;
		}
		i += 1;
	}
	return (word_count);
}

char	*ft_strdup_range(char *str, int begin, int end)
{
	int		len;
	char		*ret;
	int		str_ptr;
	int		i;

	len = end - begin + 1;
	ret = malloc(sizeof(char) * (len + 1));
	str_ptr = begin;
	i = 0;
	while (str_ptr <= end)
	{
		ret[i] = str[str_ptr];
		printf("\nFunction -> ft_strdup_range: str[%i]: %c -> ret[%i]: %c\n", str_ptr, str[str_ptr], i, ret[i]); 
		i += 1;
		str_ptr += 1;
	}
	ret[i] != '\0';
	printf("\nFunction -> ft_strdup_range: ret: %s\n", ret);
	return (ret);
}

void	place_strings(char **strings, char *str)
{
	int		i;
	int		begin;
	int		end;
	int		strings_ptr;

	i = 0;
	strings_ptr = 0;
	while (str[i] != '\0')
	{
//		printf("\nFunction -> place_string: str[%d]: %c\n", i, str[i]);
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
		{
			begin = i;
			while (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i])
			{
				i += 1;
//				printf("\nstr[%d]: %c\n", i, str[i]);
			}
			end = i - 1;
			strings[strings_ptr] = ft_strdup_range(str, begin, end);
			printf("\nFunction -> place_strings: strings[%i]: %s\n", strings_ptr, strings[strings_ptr]);
			strings_ptr += 1;
		}
		if (str[i] == '\0')
		{
			break ;
		}
		i += 1;
	}
}

void	print_strings(char **strings)
{
	int		i;

	i = 0;
	while (strings[i] != NULL)
	{
		printf("\nstring[%d]: %s\n", i, strings[i]);
		i += 1;
	}
}

char	**ft_strsplit(char *str)
{
	int		word_count;
	char		**strings;

	word_count = count_words(str);
		printf("\nword_count: %d\n", word_count);
	strings = malloc(sizeof(strings) * (word_count + 1));
	place_strings(strings, str);
	print_strings(strings);
	return (strings);
}

void	swap_str(char **str1, char **str2)
{
	char	*tmp;

	tmp = *str1;
	printf("\nFunction -> swap_str: tmp @ %p\n", &tmp);
	printf("\nFunction -> swap_str: str1 @ %p\n", &str1);
	printf("\nFunction -> swap_str: str2 @ %p\n", &str2);
	*str1 = *str2;
	*str2 = tmp;
	printf("\nFunction -> swap_str: str1 @ %p\n", &str1);
	printf("\nFunction -> swap_str: str2 @ %p\n", &str2);

}

void	swap_strings(char *str1, char *str2)
{
	char	*tmp;
	printf("\nFunction -> swap_strings: BEFORE:    ");
	printf("\nFunction -> swap_strings: str1: %s", str1);
	printf("\nFunction -> swap_strings: str2: %s", str2);
	
	printf("\n\nAFTER:\n");\

	tmp = ft_strdup_range(str1, 0, ft_strlen(str1) - 1);
	
	printf("\nFunction -> swap_strings: tmp: %s\n", tmp);
	
	free(str1);
	
	str1 = ft_strdup_range(str2, 0, ft_strlen(str2) - 1);
	
	free(str2);
	
	printf("\nFunction -> swap_strings: str1: %s\n", str1);
	
	str2 = ft_strdup_range(tmp, 0, ft_strlen(tmp) - 1);
	
	printf("\nFunction -> swap_strings: str2: %s\n", str2);
	
	free(tmp);
}

void	sort_strings(char **strings)
{
	int		word_count;
	int		strings_ptr;
	int		sorted;
	int		i;

	word_count = 0;
	i = 0;
	while (strings[i] != NULL)
	{
		i += 1;
		word_count += 1;
	}
	sorted = 0;
	while (sorted == 0)
	{
		sorted = 1;
		strings_ptr = word_count - 1;
		while (strings_ptr > 0)
		{
			if (ft_strlen(strings[strings_ptr]) < ft_strlen(strings[strings_ptr - 1]))
			{
				sorted = 0;
				printf("\nFunction -> sort_strings: strings[%i]: %s <swap> ", strings_ptr, strings[strings_ptr]);
				printf("strings[%i]: %s\n", strings_ptr - 1, strings[strings_ptr - 1]);
				swap_str(&strings[strings_ptr], &strings[strings_ptr - 1]);
			}
			strings_ptr -= 1;
		}
	}

}

void	alph_long(char *str)
{
	char		**strings;
	
	strings = ft_strsplit(str);
	printf("\nFunction -> alph_long: Before: ");
	print_strings(strings);
	sort_strings(strings);
	printf("\nAfter: ");
	print_strings(strings);
}

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		alph_long(argv[1]);
	}
	printf("\n");
	return (0);
}

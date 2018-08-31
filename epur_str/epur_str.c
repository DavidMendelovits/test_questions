#include <stdio.h>
#include <stdlib.h>


int		skip_whitespaces(char *str)
{
	int		i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
	{
		i += 1;
	}
	return (i);
}

char		*ft_strdup_range(char *str, int begin, int end)
{
	int		i;
	char		*duplicate;
	int		duplicate_ptr;
	int		range;

	range = end - begin + 1;
	i = begin;
	duplicate = malloc(sizeof(char) * (range + 1));
	duplicate_ptr = 0;
	while (i <= end)
	{
		duplicate[duplicate_ptr] = str[i];
		i += 1;
		duplicate_ptr += 1;
	}
	duplicate[duplicate_ptr] = '\0';
	return (duplicate);
}

int		ft_strlen(char *str)
{
	int		i;

	i = 0;
	if (!str)
	{
		return (0);
	}
	while (str[i])
	{
		i += 1;
	}
	return (i);
}

char		*ft_strjoin_space(char *str1, char *str2)
{
	int		str_ptr;
	char		*joined;
	int		joined_ptr;

	joined = malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2) + 2));
	joined_ptr = 0;
	str_ptr = 0;
	if (str1)
	{
		while (str1[str_ptr])
		{
			joined[joined_ptr] = str1[str_ptr];
			joined_ptr += 1;
			str_ptr += 1;
		}
	}
	if (joined_ptr > 0)
	{
		joined[joined_ptr] = ' ';
		joined_ptr += 1;
	}
	str_ptr = 0;
	while (str2[str_ptr])
	{
		joined[joined_ptr] = str2[str_ptr];
		joined_ptr += 1;
		str_ptr += 1;
	}
	joined[joined_ptr] = '\0';
	return (joined);

}

char		*epur_str(char *str)
{
	int		i;
	char		*ret;
	int		ret_ptr;
	int		begin_word;

	i = skip_whitespaces(str);
	while (str[i] != '\0')
	{
		if (str[i] != ' ' && str[i] != '\t')
		{
			begin_word = i;
			while (str[i] != ' ' && str[i] != '\t' && str[i])
			{
				i += 1;
			}
			ret = ft_strjoin_space(ret, ft_strdup_range(str, begin_word, i - 1));
		}
		else
		{
			i += 1;
		}
	}
	return (ret);
}

int		main(int argc, char **argv)
{
	if (argc == 2)
	{
		printf("epur_str: %s\n", epur_str(argv[1]));
	}
	return (0);
}


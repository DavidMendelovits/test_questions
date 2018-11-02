/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 09:32:23 by dmendelo          #+#    #+#             */
/*   Updated: 2018/10/17 11:04:47 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int					is_char(char a, char b)
{
	if (a == b)
	{
		return (1);
	}
	return (0);
}

int					count_args(char *stream)
{
	WOW();
	int					count;
	int					p;

	count = 0;
	p = 0;
	while (stream[p])
	{
		if (stream[p] == '"')
		{
			count += 1;
			p += 1;
			while (stream[p] && stream[p] != '"')
			{
				p += 1;
			}
			p += 1;
		}
		else if (stream[p] == '$' && stream[p + 1] == '(')
		{
			count += 1;
			while (stream[p] && stream[p] != ')')
			{
				p += 1;
			}
		}
		else if (stream[p] != ' ' && stream[p] != '\t')
		{
			count += 1;
			while (stream[p] && stream[p] != ' ' && stream[p] != '\t')
			{
				p += 1;
			}
		}
		else
		{
			p += 1;
		}
	}
	return (count);
}

char			*ft_strdup_range(const char *str, int begin, int end)
{
	WOW();
	int				p;
	char			*dup;
	int				dp;

	if (begin > end)
		return (NULL);
	p = begin;
	dup = malloc(sizeof(char) * (end - begin + 2));
//	bzero(dup, end - begin + 2);
	dp = 0;
	while (p <= end)
	{
		dup[dp] = str[p];
		dp += 1;
		p += 1;
	}
	dup[dp] = '\0';
	printf("dup = %s\n", dup);
	return (dup);
}

void				print_strings(char **strings)
{
	int					p;

	p = 0;
	
	while (strings[p])
	{
		printf("strings[%d] = %s\n", p, strings[p]);
		p += 1;
	}
}

char				**split_stream(char *stream)
{
	WOW();
	char				**args;
	int					p;
	int					ap;
	int					arg_count;
	int					begin;
	int					len = strlen(stream);

	arg_count = count_args(stream);
	printf("arg_count = %d\n", arg_count);
	args = malloc(sizeof(char *) * (arg_count + 1));
	p = 0;
	ap = 0;
	while(stream[p] && p < len)
	{
		if (stream[p] == '"')
		{
			begin = ++p;
			while (stream[p] && stream[p] != '"')
			{
				p += 1;
			}
			args[ap] = ft_strdup_range(stream, begin, p - 1);

			printf("args[%d] = %s\n", ap, args[ap]);
			ap += 1;
			p += 1;
		}
		else if (stream[p] == '$' && stream[p + 1] == '(')
		{
			begin = p;
			while (stream[p] && stream[p] != ')')
			{
				p += 1;
			}
			args[ap] = ft_strdup_range(stream, begin, p);

			printf("args[%d] = %s\n", ap, args[ap]);
			ap += 1;
			p += 1;
		}
		else if (stream[p] != ' ' && stream[p] != '\t')
		{
			begin = p;
			while (stream[p] && stream[p] != ' ' && stream[p] != '\t')
			{
				p += 1;
			}
			args[ap] = ft_strdup_range(stream, begin, p - 1);

			printf("args[%d] = %s\n", ap, args[ap]);
		}
		else
		{
			p += 1;
		}
	}
	printf("args[%d]\n", ap);
	args[ap] = NULL;
	print_strings(args);
	free(stream);
	return (args);
}

void				read_line(void)
{
	char				**input;
	char				buffer[1024];
	int					p;

	p = 0;
	bzero(buffer, 1024);
	write(1, "->", 2);
	while (read(0, &buffer[p], 1))
	{
		if (buffer[p] == '\n')
		{
			buffer[p] = '\0';
			break ;
		}
		p += 1;
	}
	printf("input = %s\n", buffer);
	if (!strncmp(buffer, "quit", 4))
	{
		return ;
	}
	input = split_stream(strdup(buffer));
	print_strings(input);
	read_line();
}

int					main(void)
{
	read_line();
	return (0);
}

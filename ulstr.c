/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ulstr.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 07:26:30 by dmendelo          #+#    #+#             */
/*   Updated: 2018/08/24 07:37:11 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

# define UPPERCASE "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
# define LOWERCASE "abcdefghijklmnopqrstuvwxyz"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
}

int		is_upper(char c)
{
	if (c >= 65 && c <= 90)
	{
		return (1);
	}
	return (0);
}

int		is_lower(char c)
{
	if (c >= 97 && c <= 122)
	{
		return (1);
	}
	return (0);
}

void	ulstr(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (is_upper(str[i]))
		{
			ft_putchar(LOWERCASE[str[i] - 'A']);
		}
		else if (is_lower(str[i]))
		{
			ft_putchar(UPPERCASE[str[i] - 'a']);
		}
		else
		{
			ft_putchar(str[i]);
		}
		i++;
	}
}

int		main(int argc, char **argv)
{
	if (argc == 2)
	{
		ulstr(argv[1]);
	}
	ft_putstr("\n");
	return (0);
}

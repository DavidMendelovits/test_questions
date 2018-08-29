/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_mini.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 13:44:14 by dmendelo          #+#    #+#             */
/*   Updated: 2018/08/29 14:30:31 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "count_islands.h"

void		ft_putchar(char c)
{
	write(1, &c, 1);
}

void		ft_putstr(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		ft_putchar(str[i]);
		i += 1;
	}
}

char		*ft_strdup(char *str)
{
	int		i;
	char	*duplicate;

	i = 0;
	duplicate = malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[i] != '\0')
	{
		duplicate[i] = str[i];
		i += 1;
	}
	duplicate[i] = '\0';
	return (duplicate);
}

char		*ft_strdup_range(char *str, int begin, int end)
{
	int		i;
	int		dup_ptr;
	char	*duplicate;

	i = begin;
	dup_ptr = 0;
	duplicate = malloc(sizeof(char) * (end - begin + 2));
	while (i <= end)
	{
		duplicate[dup_ptr] = str[i];
		dup_ptr += 1;
		i += 1;
	}
	duplicate[dup_ptr] = '\0';
	return (duplicate);
}

int			ft_strlen(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		i += 1;
	}
	return (i);
}

void		test_strdups()
{
	printf("\nstrdup check: %s\n", ft_strdup("It works!"));	
	printf("\nstrdup_range check: %s\n", ft_strdup_range("01234It works!13", 5, 13));
}

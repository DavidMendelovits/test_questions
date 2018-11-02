/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 10:22:36 by dmendelo          #+#    #+#             */
/*   Updated: 2018/11/02 11:35:52 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_point.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

void				print_point(t_point p)
{
	printf("[%d][%d]\n", p.y, p.x);
}
/*
static int			**init_matrix(t_point size)
{
	int					**matrix;
	int					i;
	int					p;

	matrix = malloc(sizeof(int *) * (size.y));
	i = 0;
	while (i < size.y)
	{
		matrix[i] = malloc(sizeof(int) * (size.x));
		p = 0;
		while (p < size.x)
		{
			matrix[i][p] = 0;
			p += 1;
		}
		i += 1;
	}
	return (matrix);
}
*/
void				flood_fill(char **tab, t_point size, t_point begin)
{
	t_point				new;
//	int					**visited = init_matrix(size);
	char				c;

	c = tab[begin.y][begin.x];
	if (begin.y >= 0 && begin.y < size.y && begin.x >= 0 && begin.x < size.x)
	{
		tab[begin.y][begin.x] = 'F';
	}
//	visited[begin.y][begin.x] = 1;
	if (begin.y > 0 && begin.y < size.y && begin.x >= 0 && begin.x < size.x)
	{
		new.y = begin.y - 1;
		new.x = begin.x;
		print_point(new);
		if (tab[new.y][new.x] == c)
		{
			flood_fill(tab, size, new);
		}
	}
	if (begin.y >= 0 && begin.y < size.y && begin.x > 0 && begin.x < size.x)
	{
		new.y = begin.y;
		new.x = begin.x - 1;
		print_point(new);
		if (tab[new.y][new.x] == c)
		{
			flood_fill(tab, size, new);
		}
	}
	if (begin.y >= 0 && begin.y < size.y && begin.x >= 0 && begin.x < size.x - 1)
	{
		new.y = begin.y;
		new.x = begin.x + 1;
		print_point(new);
		if (tab[new.y][new.x] == c)
		{
			flood_fill(tab, size, new);
		}
	}
	if (begin.y >= 0 && begin.y < size.y - 1 && begin.x >= 0 && begin.x < size.x)
	{
		new.y = begin.y + 1;
		new.x = begin.x;
		print_point(new);
		if (tab[new.y][new.x] == c)
		{
			flood_fill(tab, size, new);
		}
	}
}

void				print_tab(char **tab)
{
	int				i;

	i = 0;
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i += 1;
	}
}

int					count_ptrs(char **zone)
{
	int				p;

	p = 0;
	while (zone[p])
	{
		p += 1;
	}
	return (p);
}

char				**make_area(char **zone)
{
	char			**area;
	int				ptr_count;
	int				p;

	ptr_count = count_ptrs(zone);
	area = malloc(sizeof(*area) * (ptr_count + 1));
	p = 0;
	while (zone[p])
	{
		area[p] = strdup(zone[p]);
		p += 1;
	}
	area[p] = NULL;
	return (area);
}

int 				main(void)
{
	char **area;
	t_point size = {8, 5};
	t_point begin = {2, 2};
	char *zone[] = {
		"1 1 1 1 1 1 1 1",
		"1 0 0 0 1 0 0 1",
		"1 0 0 1 0 0 0 1",
		"1 0 1 1 0 0 0 1",
		"1 1 1 0 0 0 0 1",
		NULL
	};

	area = make_area(zone);
	print_tab(area);
	flood_fill(area, size, begin);
	printf("\n");
	print_tab(area);
	return (0);
}

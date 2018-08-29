/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_islands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 13:42:02 by dmendelo          #+#    #+#             */
/*   Updated: 2018/08/29 14:30:26 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "count_islands.h"

#define BUF_SIZE 1024


void		read_into_struct(char *buffer, t_island *islands)
{
	int			i;
	static int	map_line_ptr = 0;
	static int	first_malloc = 0;
	static int	times_called = 0;

	i = 0;
	printf("\nfunction read_into_struct has been called %d times\n", times_called++);
	while (buffer[i] != EOF || buffer[i] != '\n')
	{
		if (buffer[i] == '\n')
		{
			if (first_malloc == 0)
			{
				islands->map = malloc(sizeof(islands->map) * (i + 1));
				first_malloc = 1;
			}
			islands->map[map_line_ptr] = ft_strdup_range(&buffer[0], 0, i);
			printf("\nfunction -> read_into_struct: islands->map[%d] = \n%s\n", map_line_ptr, islands->map[map_line_ptr]);
			map_line_ptr += 1;

		}
		i += 1;
	}
}

void		read_map(int fd, t_island *islands)
{
	char		buffer[BUF_SIZE];
	int			i;

	i = 0;
	while (read(fd, &buffer, BUF_SIZE))
	{
		read_into_struct(buffer, islands);
		break ;
	}
}

void		count_islands(char *filename)
{
	int			fd;
	t_island	islands;

	fd = open(filename, O_RDONLY);
	read_map(fd, &islands);
}

int			main(int argc, char **argv)
{
	if (argc == 2)
	{
		count_islands(argv[1]);
	}
	test_strdups();
	ft_putstr("\n");
	return (0);
}

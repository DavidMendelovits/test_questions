#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct		s_map
{
	char		**map;
	int		row;
	int		column;
	int		row_length;
	int		rows;
	int		island_number;
	char		*overflow;
}			t_map;

int		strchr_index(char *str, char c)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			return (i);
		}
		i += 1;
	}
			printf("%s\n", map->map[map->row - 1]);
	return (i);
}

void		init_map(t_map *map)
{
	map->map = malloc(sizeof(map->map) * 100);
	map->row = 0;
	map->rows = 0;
	map->column = 0;
	map->island_number = 0;
	map->overflow = NULL;
}

char		*ft_strdup_range(char *str, int begin, int end)
{
	char		*dup;
	int		dup_ptr;
	int		str_ptr;

	dup = malloc(sizeof(char) * (end - begin + 2));
	dup_ptr = 0;
	str_ptr = begin;
	while (str_ptr <= end)
	{
		dup[dup_ptr] = str[str_ptr];
		dup_ptr += 1;
		str_ptr += 1;
	}
	dup[dup_ptr] = '\0';
	return (dup);
}

void		store_overflow(char *buffer, t_map *map, int endline)
{
	int		range;

	range = strlen(buffer) - 1;
	map->overflow = ft_strdup_range(buffer, endline + 1, range);
}

void		shift_overflow(t_map *map, int endline)
{
	char		*tmp;

	tmp = ft_strdup_range(map->overflow, endline + 1, strlen(map->overflow) - 1);
	free(map->overflow);
	map->overflow = ft_strdup_range(tmp, 0, strlen(tmp) - 1);
}

void		read_overflow(t_map *map)
{
	int		endline;
	int		overflow_len;

	printf("function -> read_overflow()\nmap->overflow = \n%s\n", map->overflow);
	if (!(endline = strchr_index(map->overflow, '\n')))
	{
		return ;
	}
	overflow_len = strlen(map->overflow);
	map->map[map->row] = ft_strdup_range(map->overflow, 0, endline - 1);
	printf("\nread from overflow: \n%s\n", map->map[map->row]);
	map->row += 1;
	map->rows += 1;
	if (endline == overflow_len - 1)
	{
		printf("\nfree(map->overflow)\n");
		free(map->overflow);
	}
	else
	{
		printf("\nshift_overflow\n");
		shift_overflow(map, endline);
		if (map->overflow[0] != EOF)
		{	
			read_overflow(map);
		}
	}
}

void		read_into_map(char *buffer, t_map *map, int endline)
{
	map->row_length = endline + 1;
	map->map[map->row] = ft_strdup_range(buffer, 0, endline - 1);
	map->row += 1;
	map->rows += 1;
	if (endline < 1023)
	{
		store_overflow(buffer, map, endline);
	}
	if (map->overflow)
	{
		read_overflow(map);
	}

}

void		print_map(t_map *map)
{
	int		i;

	i = 0;
	printf("printing map....\n");
	while (i <= map->rows)
	{
		printf("row %d: %s\n", i, map->map[i]);
		i += 1;
	}
}

void		read_map(int fd, t_map *map)
{
	char		buffer[1024];
	int		buffer_ptr;

	init_map(map);
	while (read(fd, &buffer, 1024))
	{
		if (buffer_ptr = strchr_index(buffer, '\n'))
		{
			read_into_map(buffer, map, buffer_ptr);
			print_map(map);
		}
		else
		{
			printf("invalid map size\n");
			return ;
		}
	}
}

void		count_islands(char *filename)
{
	int		fd;
	t_map		map;

	fd = open(filename, O_RDONLY);
	read_map(fd, &map);
}

int		main(int argc, char **argv)
{
	if (argc == 2)
	{
		count_islands(argv[1]);
	}
	return (0);
}


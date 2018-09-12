#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <strings.h>
#include <string.h>

typedef struct      s_map
{
    char            **map;
    int             row;
    int             column;
    int             rows;
    int             columns;
    int             island_num;
}                   t_map;

void    init_map_struct(t_map *map)
{
    printf("\nfunction-> init_map_struct\n");
    map->map = malloc(sizeof(map->map) * 100);
    map->row = 0;
    map->column = 0;
    map->rows = 0;
    map->columns = 0;
    map->island_num = 0;
}

void    extract_line(char *buffer, t_map *map, int end_line)
{
    printf("\nfunction-> extract_line\n");
    map->map[map->row] = strndup(buffer, end_line + 1);
    printf("map->map[%.2d]: %s\n", map->row, map->map[map->row]);
    map->row += 1;
    map->rows += 1;
}

void    read_map(int fd, t_map *map)
{
    char        buffer[1025];
    int         buffer_ptr;
    int         first_line;

    first_line = 1;
    buffer_ptr = 0;
    printf("\nfunction-> read_map\n");
    while (read(fd, &buffer[buffer_ptr], 1))
    {
        if (buffer[buffer_ptr] == '\n' || buffer_ptr == 1023)
        {
            if (first_line)
            {
                map->columns = buffer_ptr;
                first_line = 0;
            }
            extract_line(buffer, map, buffer_ptr - 1);
            buffer_ptr = 0;
        }
        else
        {
            buffer_ptr += 1;
        }
    }
}

void    count_island(t_map *map, int row, int column)
{
    int         island_num;
    static int  called = 0;

    island_num = map->island_num;
    printf("\nfunction-> count_island\n");
    printf("map->map[%d][%d] = %s\n", row, column, map->map[row]);
    if (map->map[row][column] == 'X')
    {
//        printf("map->map[%d][%d] = %c\n", row, column, map->map[row][column]);
        map->map[row][column] = '0' + island_num;
//        printf("map->map[%d][%d] = %c\n", row, column, map->map[row][column]);
    }
    if (column > 0 && map->map[row][column - 1] == 'X')
    {
        count_island(map, row, column - 1);
    }
    if (row > 0 && map->map[row - 1][column] == 'X')
    {
        count_island(map, row - 1, column);
    }
    if (column < map->columns - 1 && map->map[row][column + 1] == 'X')
    {
        count_island(map, row, column + 1);
    }
    if (row < map->rows - 1 && map->map[row + 1][column] == 'X')
    {
        count_island(map, row + 1, column);
    }
    printf("\ncount_island called and finished %d times\n", ++called);
}

void    print_map(t_map *map)
{
    int     i;

    i = 0;
    printf("printing map...\n");
    while (i < map->rows)
    {
        printf("%s\n", map->map[i]);
        i += 1;
    }
    printf("end print_map\n");
}

void    solve(t_map *map)
{
    printf("\nfunction-> solve\n");
    printf("map->rows = %d\n", map->rows);
    printf("map->columns = %d\n", map->columns);
    map->row = 0;
    while (map->row < map->rows && map->column < map->columns)
    {
        while (map->column < map->columns)
        {
            if (map->map[map->row][map->column] == 'X')
            {
                count_island(map, map->row, map->column);
                print_map(map);
                map->island_num += 1;
            }
            map->column += 1;
        }
        map->column = 0;
        map->row += 1;
    }        
}

void    count_islands(char *filename)
{
    int         fd;
    t_map       *map;

    printf("\nfunction-> count_islands\n");
    fd = open(filename, O_RDONLY);
    map = malloc(sizeof(map));
    init_map_struct(map);
    read_map(fd, map);
    solve(map);
    print_map(map);
    free(map);
}

int     main(int argc, char **argv)
{
    if (argc == 2)
    {
        count_islands(argv[1]);
    }
    return (0);
}

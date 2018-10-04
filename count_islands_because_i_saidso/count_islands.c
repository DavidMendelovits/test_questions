#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define WOW() printf("->%s\n", __func__)

typedef struct      s_map
{
    char            **map;
    int             x_ptr;
    int             y_ptr;
    int             x;
    int             y;
    int             island_num;
}                   t_map;

void            print_map(char **map)
{
    WOW();
    int         i;
    
    i = 0;
    while (map[i])
    {
        printf("%s\n", map[i]);
        i += 1;
    }
}

char            **read_map(t_map **map, char *file)
{
    WOW();
    int         fd;
    char        **pmap;
    char        _map[1024][1024];
    char        buf;
    int         x;
    int         y;

    fd = open(file, O_RDONLY);
    x = 0;
    y = 0;
    (*map)->x = 0;
    while ((read(fd, &buf, 1)))
    {
        if (buf != '\n' && buf)
        {
        _map[y][x] = buf;
        x += 1;
        }
        else if (buf == '\n')
        {
            printf("%s\n", _map[y]);
            _map[y][x] = '\0';
            y += 1;
            if ((*map)->x != x && (*map)->x != 0)
            {
                printf("\n mismatched line\n");
                return (NULL);
            }
            (*map)->x = x;
            x = 0;
        }
    }
    (*map)->y = y - 1;
    pmap = malloc(sizeof(char*) * (y));
    y = 0;
    while (y <= (*map)->y)
    {
        pmap[y] = strdup(_map[y]);
        y += 1;
    }
    pmap[y] = NULL;
    return (pmap);
}

void            number_island(t_map **_map, int x, int y)
{
    WOW();
    t_map       *map;
    
    map = *_map;
    printf("%c at map[%i][%i]\n", map->map[y][x], y, x);
    if (y - 1 >= map->y || y < 0 || x >= map->x || x < 0)
    {
        return ;
    }
    if (map->map[y][x] == 'X')
    {
        map->map[y][x] = map->island_num + '0';
    }
    if (y > 0 && map->map[y - 1][x] == 'X')
    {
        number_island(_map, x, y - 1);
    }
    if (y < map->y && map->map[y + 1][x] == 'X')
    {
        number_island(_map, x, y + 1);
    }
    if (x > 0 && map->map[y][x - 1] == 'X')
    {
        number_island(_map, x - 1, y);
    }
    if (x < map->x && map->map[y][x + 1] == 'X')
    {
        number_island(_map, x + 1, y);
    }
}

void            count(t_map **_map)
{
    WOW();
    t_map       *map;

    map = *_map;
    map->island_num = 0;
    map->x_ptr = 0;
    map->y_ptr = 0;
    while (map->y_ptr <= map->y)
    {
        while (map->x_ptr < map->x)
        {
            printf("map[%i][%i]\n", map->y_ptr, map->x_ptr);
            if (map->map[map->y_ptr][map->x_ptr] == 'X')
            {
                number_island(_map, map->x_ptr, map->y_ptr);
                map->island_num += 1;
                print_map((*_map)->map);
            }
            map->x_ptr += 1;
        }
        map->x_ptr = 0;
        map->y_ptr += 1;
    }
}

void            count_islands(char *file)
{
    WOW();
    t_map       *map;

    map = malloc(sizeof(t_map));
    map->map = read_map(&map, file);
    printf("\n");
    print_map(map->map);
    count(&map);
    print_map(map->map);
}

int             main(int argc, char **argv)
{
    if (argc == 2)
    {
        count_islands(argv[1]);
    }
    return (0);
}

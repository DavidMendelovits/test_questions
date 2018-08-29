#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct	s_island
{
	char	leftmost[1024];
	char	topmost[1024];
	int	filled_spots;
	int	count;
}		t_island;


void		ft_putchar(char c);
void		ft_putstr(char *str);
void		ft_strdup(char *str);

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_islands.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 13:42:12 by dmendelo          #+#    #+#             */
/*   Updated: 2018/08/29 14:30:30 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

typedef struct	s_island
{
	char	leftmost[1024];
	char	topmost[1024];
	int		filled_spots;
	int		count;
	int		valid_map:1;
	char	**map;
}		t_island;


void		ft_putchar(char c);
void		ft_putstr(char *str);
char		*ft_strdup(char *str);
char		*ft_strdup_range(char *str, int begin, int end);
int			ft_strlen(char *str);
void		test_strdups();

void		count_islands(char *filename);
void		read_map(int fd, t_island *islands);
void		read_into_struct(char *buffer, t_island *islands);


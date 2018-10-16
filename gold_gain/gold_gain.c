/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gold_gain.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 09:25:48 by dmendelo          #+#    #+#             */
/*   Updated: 2018/10/11 11:09:47 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

typedef struct		s_miner
{
	int				x;
	int				y;
}					t_miner;

int					choose_start(int **mine, int n)
{
	printf("->%s\n", __func__);
	int						start;
	int						start_value;

	start = n - 1;
	start_value = 0;
	while (--n >= 0)
	{
		printf("\n(%d,%d) = %d\n", n, 0, mine[n][0]);
		if (mine[n][0] > start_value)
		{
			printf("%d > %d\n", mine[n][0], start_value);
			start_value = mine[n][0];
			start = n;
		}
	}
	printf("returns: %d\n", start);
	return (start);
}

int				take_gold(int **mine, t_miner *miner, int n, int gold)
{
	printf("->%s\n", __func__);
	int				up_right = 0;
	int				down_right = 0;
	int				right = 0;
	
	if (miner->y > 0)
	{
		printf("\n(%d,%d) = %d\n", miner->y - 1, miner->x + 1, mine[miner->y - 1][miner->x + 1]);
		up_right = mine[miner->y - 1][miner->x + 1];
	}
	if (miner->y < n - 1)
	{
		printf("\n(%d,%d) = %d\n", miner->y + 1, miner->x + 1, mine[miner->y + 1][miner->x + 1]);
		down_right = mine[miner->y + 1][miner->x + 1];
	}
	printf("(%d,%d) = %d\n", miner->y + 1, miner->x, mine[miner->y][miner->x + 1]);
	right = mine[miner->y][miner->x + 1];
	miner->x += 1;
	if (up_right > down_right && up_right > right)
	{
		miner->y -= 1;
		return (up_right);
	}
	else if (down_right > up_right && down_right > right)
	{
		miner->y += 1;
		return (down_right);
	}
	return (right);
}

void			print_matrix(int **matrix, int n)
{
	printf("->%s\n", __func__);
	int			i;
	int			j;


	j = 0;
	while (j < n)
	{
		i = 0;
		while (i < n)
		{
			printf("%d ", matrix[j][i]);
			i += 1;
		}
		printf("\n");
		j += 1;
	}
}

int				gold_gain(int **mine, int n)
{
	printf("->%s\n", __func__);
	int						gold;
	t_miner					miner;
	int						column;

	print_matrix(mine, 3);
	column = 0;
	gold = 0;
	miner.x = 0;
	miner.y = choose_start(mine, n);
	printf("(%d,%d) ->", miner.y, miner.x);
	gold += mine[miner.y][miner.x];
	while (miner.x < n - 1)
	{
		if (miner.y < n && miner.y >= 0)
		{
			gold += take_gold(mine, &miner, n, 0);
			printf("(%d,%d) ->", miner.y, miner.x);
		}
	}
	return (gold);
}



int				main()
{
	int			**matrix = malloc(sizeof(*matrix) * 3);
	matrix[0] = malloc(sizeof(int) * 3);
	matrix[1] = malloc(sizeof(int) * 3);
	matrix[2] = malloc(sizeof(int) * 3);
	matrix[0][0] = 1;
	matrix[0][1] = 2;
	matrix[0][2] = 3;
	matrix[1][0] = 3;
	matrix[1][1] = 4;
	matrix[1][2] = 8;
	matrix[2][0] = 9;
	matrix[2][1] = 6;
	matrix[2][2] = 7;
	print_matrix(matrix, 3);
	printf("gold gained: %d\n", gold_gain(matrix, 3));
	return (0);
}

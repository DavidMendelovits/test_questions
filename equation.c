/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 08:58:28 by dmendelo          #+#    #+#             */
/*   Updated: 2018/11/02 09:15:22 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void			equation(int n)
{
	int				a;
	int				b;
	int				c;

	a = 0;
	while (a < 10)
	{
		b = 0;
		while (b < 10)
		{
			c = 0;
			while (c < 10)
			{
				if (((a * 10) + b) + ((c * 10) + a) == n)
				{
					printf("A = %d, B = %d, C = %d\n", a, b, c);
				}
				c += 1;
			}
			b += 1;
		}
		a += 1;
	}
}

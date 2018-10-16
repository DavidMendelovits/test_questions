/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bits.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 09:07:45 by dmendelo          #+#    #+#             */
/*   Updated: 2018/10/11 09:24:21 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>


void			print_bits(unsigned char octet)
{
	int					i;

	i = 8;
	while (i--)
	{
		if ((octet >> i) & 1)
		{
			printf("1");
		}
		else
		{
			printf("0");
		}
	}
}

unsigned char	reverse_bits(unsigned char octet)
{
	unsigned char		ret;
	int					i;
	
	i = 0;
	ret = 0;
	while (i < 8)
	{
		if ((octet >> i) & 1)
			ret |= 1;
		i += 1;
		if (i < 8)
			ret <<= 1;

	}
	return (ret);
}

int				main(int argc, char **argv)
{
	if (argc == 2)
	{
		print_bits((unsigned char)(argv[1][0]));
		printf("\n");
		print_bits(reverse_bits((unsigned char)(argv[1][0])));
		printf("\n");
	}
	return (0);

}

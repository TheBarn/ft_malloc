/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 16:45:08 by barnout           #+#    #+#             */
/*   Updated: 2018/09/12 15:26:46 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	dump_table(t_alloc *alc)
{
	int		len;
	int		i;
	int		j;
	int		start;

	i = alc->min;
	start = 0;
	while (i <= alc->max)
	{
		printf("SIZE %d: ", power_of_two(i));
		len = power_of_two(alc->max - i);
		j = 0;
		while (j < len)
		{
//			printf("i : %d\n", start + j);
			printf("%p ", alc->table[start + j]);
			j++;
		}
		printf("\n");
		start += len;
		i++;
	}
}

void    print_mem(char *ptr, int size)
{
	int i;

	i = 0;
	printf("0x");
	while (i < size)
	{
		printf("%02hhx", ptr[i]);
		i++;
	}
	printf("\n");
}

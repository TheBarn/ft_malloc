/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 16:45:08 by barnout           #+#    #+#             */
/*   Updated: 2018/09/13 11:58:22 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	dump_table(t_alloc *alc)
{
	int		len;
	int		i;
	int		j;
	int		start;
	void	*bl;

	i = alc->min;
	start = 0;
	while (i <= alc->max)
	{
		printf("SIZE %d: ", power_of_two(i));
		len = power_of_two(alc->max - i);
		j = 0;
		while (j < len)
		{
			bl = alc->table[start + j];
			if (bl && ((t_head *)bl)->free == 1)
				printf("\033[32m%p\033[0m ", bl);
			else if (bl && ((t_head *)bl)->free == 0)
				printf("\033[31m%p\033[0m ", bl);
			else
				printf("%p ", bl);
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

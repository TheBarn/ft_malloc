/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 11:29:11 by barnout           #+#    #+#             */
/*   Updated: 2018/09/20 15:54:59 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

extern t_dib	*g_dib;

void	print_block(void *bl)
{
	t_head	*h;
	int		size;
	int		j;
	int		c;

	h = (t_head*)bl;
	size = get_block_size(bl);
	j = 0;
	if (h->free)
		c = GREEN;
	else
		c = RED;
	printf("\033[%dm", c);
	while (j < size / 16)
	{
		printf(" ");
		j++;
	}
	printf("\033[0m");
}

void	print_space(int size)
{
	int		i;

	i = 0;
	while (i < size / 16)
	{
		printf(" ");
		i++;
	}
}

void	print_ind(t_alloc *alc, int ind)
{
	int		sp;
	int		nb;
	int		j;
	int		r;

	sp = count_digit(power_of_two(alc->max)) + 2;
	nb = power_of_two(ind);
	printf("%d", nb);
	j = 0;
	r = sp - count_digit(nb);
	while (j++ < r)
		printf(" ");
}

void	print_line(t_alloc *alc, int ind)
{
	int		s;
	int		len;
	int		i;
	int		ad;
	int		size;

	print_ind(alc, ind);
	size = power_of_two(ind);
	s = find_seq_start(alc, ind);
	len = power_of_two(alc->max - ind);
	i = 0;
	while (i < len)
	{
		ad = (alc->table)[s + i];
		if (ad)
			print_block(get_block(alc, ad));
		else
			print_space(size);
		i++;
	}
	printf("\n");
}

void	print_total(t_alloc *alc)
{
	int		i;
	int		size;
	int		tot;
	void	*bl;
	int		sp;

	sp = count_digit(power_of_two(alc->max)) + 2;
	i = 0;
	printf("\ntot");
	while (i++ < sp - 3)
		printf(" ");
	i = 0;
	tot = sum_power_of_two(alc->min, alc->max);
	while (i < tot)
	{
		bl = &((alc->zn)[i]);
		print_block(bl);
		size = get_block_size(bl);
		if (!size)
			break ;
		i += size;
	}
	printf("\n");
}

void	print_zone(t_alloc *alc, char *op, void *arg)
{
	int		ind;
	int		up;

	if (VISU)
	{
		up = alc->max - alc->min + 3 + 7;
		printf("\033[%dA", up);
		printf("\tCurrent operation: %s ", op);
		if (ft_strcmp("malloc", op) == 0 && arg)
			printf("of size %d             ", *((int *)arg));
		else if (ft_strcmp("free", op) == 0 && arg)
			printf("pointer %p             ", arg);
		else if (ft_strcmp("realloc", op) == 0 && arg)
			printf("of size %d             ", *((int *)arg));
		printf("\n\n");
		ind = alc->max;
		while (ind >= alc->min)
		{
			print_line(alc, ind);
			ind--;
		}
		print_total(alc);
		printf("\n\n\n\n\n");
		usleep(SPEED);
	}
}

int		find_zone_ind(t_alloc *alc)
{
	int		i;

	i = 0;
	if (alc->max == TINY_MAX)
	{
		while (i < g_dib->tiny_nb && (g_dib->tiny_alc)[i] != alc)
			i++;
	}
	else
	{
		while (i < g_dib->small_nb && (g_dib->small_alc)[i] != alc)
			i++;
	}
	return (i);
}

void	print_header(t_alloc *alc)
{
	int		i;
	int		size;

	if (VISU)
	{
		if (!alc)
			printf("\033[2J");
		printf("\033[H");
		printf("\n\tNUMBER OF ZONES:\n\tTiny Zones : %d\t\tSmall Zones \
				: %d\t\tBig Zones : %d\n\n", \
			   g_dib->tiny_nb, g_dib->small_nb, g_dib->big_nb);
		if (alc)
		{
			printf("\tSelected Zone:\t");
			if (alc->max == TINY_MAX)
				printf("tiny #");
			else
				printf("small #");
			printf("%d\n\n", find_zone_ind(alc) + 1);
			i = 0;
			size = alc->max - alc->min + 3 + 7;
			while (i++ < size)
				printf("\n");
		}
		else
			usleep(SPEED);
	}
}

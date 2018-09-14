/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 11:29:11 by barnout           #+#    #+#             */
/*   Updated: 2018/09/14 16:05:36 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	print_block(void *bl)
{
	t_head	*h;
	int		size;
	int		j;
	int		c;

	h = (t_head*)bl;
	size = h->size;
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

	sp = ft_strlen(ft_itoa(power_of_two(alc->max))) + 2;
	nb = power_of_two(ind);
	printf("%d", nb);
	j = 0;
	r = sp - ft_strlen(ft_itoa(nb));
	while (j++ < r)
		printf(" ");
}

void	print_line(t_alloc *alc, int ind)
{
	int		s;
	int		len;
	int		i;
	void	*bl;
	int		size;

	print_ind(alc, ind);
	size = power_of_two(ind);
	s = find_seq_start(alc, ind);
	len = power_of_two(alc->max - ind);
	i = 0;
	while (i < len)
	{
		bl = (alc->table)[s + i];
		if (bl)
			print_block(bl);
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

	sp = ft_strlen(ft_itoa(power_of_two(alc->max))) + 2;
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
		size = ((t_head *)bl)->size;
		if (!size)
			break;
		i += size;
	}
	printf("\n");
}

void	print_zone(t_alloc *alc, char *op)
{
	int		ind;
	int		up;

	up = alc->max - alc->min + 3 + 7;
	printf("\033[%dA", up);
	printf("\tCurrent operation: %s              \n\n", op);
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

int		find_zone_ind(t_dib *dib, t_alloc *alc)
{
	int		i;

	i = 0;
	if (alc->max == TINY_MAX)
	{
		while (i < dib->tiny_nb && (dib->tiny_alc)[i] != alc)
			i++;
	}
	else
	{
		while (i < dib->small_nb && (dib->small_alc)[i] != alc)
			i++;
	}
	return (i);
}

void	print_header(t_dib *dib, t_alloc *alc)
{
	int		i;
	int		size;

	printf("\033[H");
	printf("\n\tNUMBER OF ZONES:\n\tTiny Zones : %d\t\tSmall Zones : %d\t\tBig Zones : %d\n\n", dib->tiny_nb, dib->small_nb, dib->big_nb);
	if (alc)
	{
		printf("\tSelected Zone:\t");
		if (alc->max == TINY_MAX)
			printf("tiny #");
		else
			printf("small #");
		printf("%d\n\n", find_zone_ind(dib, alc) + 1);
		i = 0;
		size = alc->max - alc->min + 3 + 7;
		while (i++ < size)
			printf("\n");
	}
	else
		usleep(SPEED);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 09:07:14 by barnout           #+#    #+#             */
/*   Updated: 2018/09/19 12:42:51 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_dib *g_dib = NULL;

int		find_fit(t_alloc *alc, size_t size)
{
	int		fit;

	fit = alc->min;
	while (power_of_two(fit) - HEAD_SIZE < size && fit < alc->max)
		fit++;
	return (fit);
}

int		find_in_seq(t_alloc *alc, int s, int len)
{
	int		i;
	t_head	*h;
	void	*bl;

	i = 0;
	bl = NULL;
	while (i < len)
	{
		if (alc->table[s + i])
		{
			h = (t_head *)(alc->table[s + i]);
			if (h->free == 1)
			{
				bl = alc->table[s + i];
				break ;
			}
		}
		i++;
	}
	if (bl)
		return (s + i);
	else
		return (-1);
}

int		find_block_index(t_alloc *alc, int fit)
{
	int		ind;
	int		s;
	int		len;

	s = find_seq_start(alc, fit);
	len = sum_power_of_two(0, alc->max - fit);
	ind = find_in_seq(alc, s, len);
	if (ind == -1)
	{
		alc->left = power_of_two(fit - 1);
		return (-1);
	}
	return (ind);
}

void	*xor_size(void *ptr, int size)
{
	return ((void *)((uintptr_t)ptr ^ size));
}

void	*find_buddy(void *bl)
{
	void		*bud;
	t_head		*h;

	h = (t_head *)bl;
	bud = xor_size(bl, h->size);
	return (bud);
}
//TODO get rid of buddies
void	*split_block(t_alloc *alc, int ind, int fit)
{
	void	*bl;
	int		bl_size;

	ft_putchar('\n');
	ft_putstr("SPLIT:\n");
	ft_putnbr(ind);
	ft_putchar('\n');
	ft_putnbr(fit);
	ft_putchar('\n');
	bl = alc->table[ind];
	ft_putchar('a');
	bl_size = ((t_head *)bl)->size;
	ft_putchar(((t_head *)bl)->sym);
	ft_putnbr(bl_size);
	ft_putchar('b');
	if (fit == power_of_two_ind(bl_size))
	{
		((t_head *)bl)->free = 0;
		return (bl);
	}
	ft_putchar('c');
	alc->table[ind] = NULL;
	ft_putchar('d');
	ind = write_header(alc, bl, 1, bl_size / 2);
	ft_putchar('e');
	ft_putchar('\n');
	ft_putptr(bl);
	ft_putchar('\n');
	ft_putchar('f');
	show_alloc_mem();
	ft_putptr((void *)alc);
	ft_putchar('\n');
	ft_putchar('\n');
	ft_putnbr(bl_size);
	ft_putchar('\n');
	write_header(alc, bl + bl_size / 2, 1, bl_size / 2);
	ft_putchar('g');
	print_zone(alc, "malloc", NULL);
	ft_putchar('h');
	bl = split_block(alc, ind, fit);
	ft_putchar('i');
	return (bl);
}

void	*ft_big_malloc(size_t size)
{
	void	*bl;

	bl = mmap(NULL, size + HEAD_SIZE, PROT_READ | PROT_WRITE, \
				MAP_ANON | MAP_PRIVATE, -1, 0);
	if (!bl)
		throw_error("Error: mmap: no space found\n");
	if (g_dib->big_nb >= \
		(getpagesize() - ((int)sizeof(t_dib)) / 3) / (int)sizeof(t_alloc *))
		double_dib_size();
	(g_dib->big_alc)[g_dib->big_nb] = bl;
	g_dib->big_nb += 1;
	return (bl + HEAD_SIZE);
}

//TODO  munmap
void	*malloc(size_t size)
{
	t_alloc *alc;
	int		fit;
	int		ind;
	void	*bl;

	ini_dib();
	ft_putstr("\nmalloc: ");
	ft_putnbr(size);
	ft_putchar('\n');
	if (size > power_of_two(SMALL_MAX) / 100 - HEAD_SIZE)
		bl = ft_big_malloc(size);
	ft_putchar('a');
	ind = -1;
	ft_putchar('b');
	while (ind < 0)
	{
		ft_putchar('c');
		alc = get_alloc_zone(size);
		ft_putchar('d');
		fit = find_fit(alc, size);
		ft_putchar('e');
		ind = find_block_index(alc, fit);
		ft_putchar('f');
		ft_putnbr(ind);
		ft_putchar('g');
	}
	ft_putchar('h');
	print_zone(alc, "malloc", &size);
	ft_putchar('i');
	bl = split_block(alc, ind, fit);
	ft_putchar('j');
	print_zone(alc, "malloc", &size);
	ft_putstr("\nptr: ");
	ft_put_size_t((size_t)(bl + HEAD_SIZE));
	ft_putchar('\n');
	return (bl + HEAD_SIZE);
}

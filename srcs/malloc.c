/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 09:07:14 by barnout           #+#    #+#             */
/*   Updated: 2018/09/19 15:29:26 by barnout          ###   ########.fr       */
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

int		get_ad(t_alloc *alc, void *bl)
{
	return ((int)((uintptr_t)bl - (uintptr_t)alc));
}

void	*get_block(t_alloc *alc, int ad)
{
	if (ad > 0)
		return ((void *)alc + ad);
	else
		return ((void *)alc);
}

int		find_in_seq(t_alloc *alc, int s, int len)
{
	int		i;
	t_head	*h;
	int		ad;

	i = 0;
	ad = 0;
	while (i < len)
	{
		if (alc->table[s + i])
		{
			h = (t_head *)(get_block(alc, alc->table[s + i]));
			if (h->free == 1)
			{
				ad = alc->table[s + i];
				break ;
			}
		}
		i++;
	}
	if (ad)
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

void	*find_buddy(t_alloc *alc, void *bl)
{
	void		*bud;
	t_head		*h;
	int			bl_size;
	int			bl_ad;
	int			bud_ad;

	h = (t_head *)bl;
	bl_size = h->size;
	bl_ad = (void *)alc - bl;
	bud_ad = bl_ad ^ bl_size;
	bud = (void *)alc + bud_ad;
	return (bud);
}
//TODO get rid of buddies
void	*split_block(t_alloc *alc, int ind, int fit)
{
	void	*bl;
	int		bl_size;
	int		ad;
	void	*bud;

	ft_putstr("SPLIT:\n");
	ft_putnbr(ind);
	ft_putchar('\n');
	ft_putnbr(fit);
	ft_putchar('\n');
	ad = alc->table[ind];
	bl = get_block(alc, ad);
	bl_size = ((t_head *)bl)->size;
	ft_putchar(((t_head *)bl)->sym);
	ft_putnbr(bl_size);
	if (fit == power_of_two_ind(bl_size))
	{
		((t_head *)bl)->free = 0;
		return (bl);
	}
	alc->table[ind] = 0;
	ind = write_header(alc, bl, 1, bl_size / 2);
	ft_putptr(bl);
	ft_putchar('\n');
	show_alloc_mem();
	ft_putptr((void *)alc);
	ft_putchar('\n');
	ft_putchar('\n');
	ft_putnbr(bl_size);
	ft_putchar('\n');
	bud = find_buddy(alc, bl);
	write_header(alc, bud, 1, bl_size / 2);
	print_zone(alc, "malloc", NULL);
	bl = split_block(alc, ind, fit);
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
	ind = -1;
	while (ind < 0)
	{
		alc = get_alloc_zone(size);
		fit = find_fit(alc, size);
		ind = find_block_index(alc, fit);
		ft_putnbr(ind);
	}
	print_zone(alc, "malloc", &size);
	bl = split_block(alc, ind, fit);
	print_zone(alc, "malloc", &size);
	ft_putstr("\nptr: ");
	ft_put_size_t((size_t)(bl + HEAD_SIZE));
	ft_putchar('\n');
	return (bl + HEAD_SIZE);
}

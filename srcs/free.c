/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 09:41:40 by barnout           #+#    #+#             */
/*   Updated: 2018/09/20 17:20:39 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

extern t_dib	*g_dib;

int		get_block_size(void *bl)
{
	t_head	*h;
	int		size;
	int		bl_size;

	h = (t_head *)bl;
	size = h->size;
	bl_size = sup_power_of_two(size);
	return (bl_size);
}

void	erase_buddies(t_alloc *alc, void *bl, void *bud)
{
	int		s;
	int		ind;
	int		len;
	int		i;
	int		j;
	int		bl_ad;
	int		bud_ad;

	ind = power_of_two_ind(get_block_size(bl));
	s = find_seq_start(alc, ind);
	len = power_of_two(alc->max - ind);
	i = 0;
	j = 0;
	bl_ad = get_ad(alc, bl);
	bud_ad = get_ad(alc, bud);
	while (i < len)
	{
		if ((alc->table)[s + i] == bl_ad || (alc->table)[s + i] == bud_ad)
		{
			(alc->table)[s + i] = 0;
			j++;
		}
		if (j == 2)
			break ;
		i++;
	}
}

int		merge_bud(t_alloc *alc, void *bl)
{
	void	*bud;
	t_head	*bh;
	int		size;

	size = get_block_size(bl);
	if ((size_t)size == power_of_two(alc->max))
		return (0);
	bud = find_buddy(alc, bl);
	bh = (t_head*)bud;
	if (bh && bh->sym == SYM && size == get_block_size(bud) && bh->free == 1)
	{
		erase_buddies(alc, bl, bud);
		if (bud < bl)
			bl = bud;
		bh->sym = 0;
		write_header(alc, bl, 1, 2 * size);
		if (alc->left < 2 * size)
			alc->left = 2 * size;
		print_zone(alc, "free", NULL);
		merge_bud(alc, bl);
	}
	return (0);
}

t_alloc	*search_big_zone(void *ptr)
{
	int		i;

	i = 0;
	while (i < g_dib->big_nb)
	{
		if (ptr == (g_dib->big_alc)[i])
			return ((t_alloc *)ptr);
		i++;
	}
	return (NULL);
}

t_alloc	*find_zone(void *ptr)
{
	t_alloc *alc;
	int		i;

	i = 0;
	while (i < g_dib->tiny_nb)
	{
		alc = (g_dib->tiny_alc)[i];
		if (ptr >= alc->zn && ptr < alc->zn + power_of_two(alc->max))
			return (alc);
		i++;
	}
	i = 0;
	while (i < g_dib->small_nb)
	{
		alc = (g_dib->small_alc)[i];
		if (ptr >= alc->zn && ptr < alc->zn + power_of_two(alc->max))
			return (alc);
		i++;
	}
	alc = search_big_zone(ptr);
	return (alc);
}

void	free(void *ptr)
{
	void	*bl;
	t_head	*h;
	t_alloc	*alc;

	ft_putstr("\nfree: ");
	ft_putptr(ptr);
	ft_putchar('\n');
	if (ptr)
	{
		ft_putchar('a');
		ini_dib();
		alc = find_zone(ptr);
		ft_putchar('b');
		if (!alc)
		{
			throw_error("Error: pointer being freed was not allocated\n");
			return ;
		}
		print_header(alc);
		ft_putchar('c');
		bl = ptr - HEAD_SIZE;
		h = (t_head *)bl;
		ft_putchar(h->sym);
		ft_putnbr(h->free);
		ft_putchar('d');
		if (h->sym != SYM || h->free != 0)
			throw_error("Error: pointer being freed was not allocated\n");
		else if (alc != ptr)
		{
			ft_putchar('e');
			h->free = 1;
			ft_putchar('f');
			merge_bud(alc, bl);
			ft_putchar('g');
			print_zone(alc, "free", ptr);
		}
	}
}

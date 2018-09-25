/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 09:41:40 by barnout           #+#    #+#             */
/*   Updated: 2018/09/25 11:40:38 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

extern t_dib	*g_dib;

int		get_block_size(t_alloc *alc, void *bl)
{
	t_head	*h;
	int		size;
	int		bl_size;
	int		tmp;
	int		min;

	h = (t_head *)bl;
	size = h->size;
//	ft_putstr("SIZE IN BLOCK: ");
//	ft_putnbr(size);
//	ft_putstr("\nBLOCK SIZE: ");
	bl_size = alc->size;
	min = power_of_two(alc->min);
	while (bl_size >= size + HEAD_SIZE && bl_size >= min)
	{
		tmp = bl_size;
		bl_size /= 2;
	}
//	ft_putnbr(tmp);
//	ft_putchar('\n');
//	bl_size = sup_power_of_two(size + HEAD_SIZE);
	return (tmp);
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

	ind = power_of_two_ind(get_block_size(alc, bl));
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

//look left then look right becarful with the size in the header, return void
int		merge_bud(t_alloc *alc, void *bl)
{
	void	*bud;
	t_head	*bh;
	int		size;

	size = get_block_size(alc, bl);
	if ((size_t)size == power_of_two(alc->max))
		return (0);
	bud = find_buddy(alc, bl);
	bh = (t_head*)bud;
	if (bh && bh->sym == SYM && size == get_block_size(alc, bud) && bh->free == 1)
	{
		erase_buddies(alc, bl, bud);
		if (bud < bl)
			bl = bud;
		bh->sym = 0;
		write_header(alc, bl, 1, 2 * size);
		if (alc->left < 2 * size)
			alc->left = 2 * size;
//		print_zone(alc, "free", NULL);
		merge_bud(alc, bl);
	}
	return (0);
}

//check if it is correct
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
	//make only one while
	while (i < g_dib->tiny_nb)
	{
		alc = (g_dib->tiny_alc)[i];
		//change with alc->size
		if (ptr >= alc->zn && ptr < alc->zn + power_of_two(alc->max))
			return (alc);
		i++;
	}
	i = 0;
	while (i < g_dib->small_nb)
	{
		//change with alc->size
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

	if (ptr)
	{
		ini_dib();
		alc = find_zone(ptr);
		//do nothing if it is the case, maybe put a DEBUG macro
		if (!alc)
		{
			throw_error("Error: pointer being freed was not allocated\n");
			return ;
		}
//		print_header(alc);
		bl = ptr - HEAD_SIZE;
		h = (t_head *)bl;
		//same for DEBUG
		if (h->sym != SYM || h->free != 0)
			throw_error("Error: pointer being freed was not allocated\n");
		//should be alc->zn, I don't understand this condition
		else if (alc != ptr)
		{
			h->free = 1;
			merge_bud(alc, bl);
//			print_zone(alc, "free", ptr);
		}
	}
}

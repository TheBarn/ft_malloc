/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 09:07:14 by barnout           #+#    #+#             */
/*   Updated: 2018/09/25 12:33:53 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_dib *g_dib = NULL;

/*
//fit should be with real block size
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
	int		ad;

	ad = (int)((uintptr_t)bl - (uintptr_t)(alc->zn));
	return (ad);
}

void	*get_block(t_alloc *alc, int ad)
{
	if (ad > 0)
		return (alc->zn + ad);
	else
		return (alc->zn);
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
}*/

//run through alc twice and return bl (alc, size)
void	*find_block(t_alloc *alc, int mem_size)
{
	void	*bl;
	t_head	*h;
	int		bl_size;
	int		i;

	bl = alc->zn;
	i = 0;
	while (i < alc->size)
	{
		h = (t_head *)bl;
		if (h->sym != SYM)
			throw_error('not a block');
		if (h->free == 1 && h->size <= mem_size)
			return (bl);
		bl_size = get_block_size(alc, bl);
		i += bl_size;
		bl += bl_size;
	}
	throw_error('no free block');
	return (NULL);
}
/*
int		find_block(t_alloc *alc, int size)
{
	int		ind;
	int		s;
	int		len;
	int		tmp;

	tmp = fit;
	ind = -1;
	while (ind == -1 && tmp <= alc->max)
	{
		s = find_seq_start(alc, tmp);
		len = power_of_two(alc->max - tmp);
		ind = find_in_seq(alc, s, len);
		tmp++;
	}
	if (ind == -1)
	{
		alc->left = power_of_two(fit - 1);
//		ft_putstr("HEY");
		return (-1);
	}
	return (ind);
}
*/
/*
void	*find_buddy(t_alloc *alc, void *bl)
{
	void		*bud;
	int			bl_size;
	int			bl_ad;
	int			bud_ad;

	bl_size = get_block_size(alc, bl);
	bl_ad = get_ad(alc, bl);
	bud_ad = bl_ad ^ bl_size;
	bud = get_block(alc, bud_ad);
	return (bud);
}
*/

void	split_block(t_alloc *alc, void *bl, int mem_size)
{
	int		bl_size;
	//available mem size in half block
	int		half_av_size;
	t_head	*h;

	h = (t_head *)bl;
	bl_size = get_block_size(alc, bl);
	half_av_size = (bl_size / 2) - HEAD_SIZE;
	//put TINY_MIN_BL_SIZE in alc moron
	if (bl_size / 2 < TINY_MIN_BL_SIZE || (h->size >= mem_size && half_av_size < mem_size))
		write_header(bl, 0, mem_size);
	else
	{
		write_header(bl, 1, half_av_size);
		write_header(bl + (bl_size / 2), 1, half_av_size);
		split_block(alc, bl, mem_size);
	}
}

//(alc, bl, size) returns nothing, only splits and write headers
void	*split_block(t_alloc *alc, int ind, int size)
{
	void	*bl;
	int		bl_size;
	int		ad;

	ad = alc->table[ind];
	bl = get_block(alc, ad);
	bl_size = get_block_size(alc, bl);
	if (bl_size / 2 < (int)power_of_two(alc->min) || (bl_size >= size + HEAD_SIZE && (bl_size / 2) < size + HEAD_SIZE))
	{
		((t_head *)bl)->free = 0;
		((t_head *)bl)->size = size;
		return (bl);
	}
	alc->table[ind] = 0;
	ind = write_header(alc, bl, 1, bl_size / 2 - HEAD_SIZE);
	write_header(alc, bl + bl_size / 2, 1, bl_size / 2 - HEAD_SIZE);
//	print_zone(alc, "malloc", NULL);
	bl = split_block(alc, ind, size);
	return (bl);
}

//to verify, it looks terrible
void	*ft_big_malloc(size_t size)
{
	void	*bl;

	bl = ft_mmap(size + HEAD_SIZE);
	if (g_dib->big_nb >= \
		(getpagesize() - ((int)sizeof(t_dib)) / 3) / (int)sizeof(t_alloc *))
		double_dib_size();
	(g_dib->big_alc)[g_dib->big_nb] = bl;
	g_dib->big_nb += 1;
	return (bl + HEAD_SIZE);
}

//TODO rationalize mmap 
//TODO  munmap
void	*malloc(size_t size)
{
	t_alloc *alc;
	void	*bl;

	ft_putstr("malloc: ");
	ft_put_size_t(size);
	ini_dib();
	if (size > power_of_two(SMALL_MAX) / 100 - HEAD_SIZE) //replace with SMALL_LIM
	{
		bl = ft_big_malloc(size);
		return (bl);
	}
	//verify in get alloc that the zone has enough space
	alc = get_alloc_zone(size);
	find_block(alc, (int)size);
//	print_zone(alc, "malloc", &size);
	//split block returns nothing, it does only splits
	split_block(alc, ind, (int)size);
//	print_zone(alc, "malloc", &size);
	ft_putstr("\n");
//	show_dib_state();
	return (bl + HEAD_SIZE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 09:07:14 by barnout           #+#    #+#             */
/*   Updated: 2018/09/27 15:17:47 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	*find_block(t_alloc *alc, int mem_size)
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
			return (NULL);
		if (h->free == 1 && h->size >= mem_size)
			return (bl);
		bl_size = get_block_size(alc, bl);
		i += bl_size;
		bl += bl_size;
	}
	return (NULL);
}

void		split_block(t_alloc *alc, void *bl, int mem_size)
{
	int		bl_size;
	int		half_av_size;
	t_head	*h;
	void	*bud;

	h = (t_head *)bl;
	bl_size = get_block_size(alc, bl);
	half_av_size = (bl_size / 2) - HEAD_SIZE;
	if (h->size >= mem_size && half_av_size < mem_size)
		write_header(bl, 0, 0, mem_size);
	else
	{
		write_header(bl, 1, 0, half_av_size);
		bud = bl + (bl_size / 2);
		write_header(bud, 1, 1, half_av_size + (bl_size % 2));
		if (bl_size % 2)
			((t_head *)bud)->offset = 1;
		split_block(alc, bl, mem_size);
	}
}

static void	*ft_big_malloc(size_t size)
{
	void		*bl;
	t_big_head	*h;

	bl = ft_mmap(size + HEAD_SIZE);
	if (!bl)
		return (bl);
	if (!is_enough_dib_left(g_dib->big_nb))
		double_dib_size();
	h = (t_big_head *)bl;
	h->size = size;
	(g_dib->big_alc)[g_dib->big_nb] = bl;
	g_dib->big_nb += 1;
	return (bl + BIG_HEAD_SIZE);
}

void		*ft_malloc(size_t size)
{
	t_alloc *alc;
	void	*bl;

	if (size > SMALL_LIM)
		return (ft_big_malloc(size));
	alc = get_alloc_zone((int)size);
	if (!alc)
		return (NULL);
	bl = find_block(alc, (int)size);
	if (!bl)
		return (NULL);
	split_block(alc, bl, (int)size);
	return (bl + HEAD_SIZE);
}

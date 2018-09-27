/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 15:08:15 by barnout           #+#    #+#             */
/*   Updated: 2018/09/27 15:22:52 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	*find_buddy(t_alloc *alc, void *bl)
{
	int		bl_size;
	t_head	*h;
	char	side;

	bl_size = get_block_size(alc, bl);
	h = (t_head *)bl;
	side = h->side;
	if (side == 0)
		return (bl + bl_size);
	return (bl - bl_size);
}

static char	get_side(t_alloc *alc, void *bl, int bl_size)
{
	char	side;
	void	*bud;
	t_head	*bh;

	if (bl + bl_size > alc->zn + alc->size)
		return (1);
	bud = bl + bl_size;
	bh = (t_head *)bud;
	side = bh->side;
	return (1 - side);
}

static void	erase_bud(t_alloc *alc, void *bl, void *bud, int bl_size)
{
	void	*tmp;
	char	side;

	if (bud < bl)
	{
		tmp = bl;
		bl = bud;
		bud = tmp;
	}
	ft_memset(bud, TRASH, HEAD_SIZE);
	side = get_side(alc, bl, 2 * bl_size);
	write_header(bl, 1, side, 2 * bl_size - HEAD_SIZE);
	merge_bud(alc, bl);
}

void		merge_bud(t_alloc *alc, void *bl)
{
	void	*bud;
	t_head	*bh;
	int		bud_size;
	int		bl_size;

	bud = find_buddy(alc, bl);
	bh = (t_head *)bud;
	if (bud < alc->zn + alc->size && bud >= alc->zn \
						&& bh->sym == SYM && bh->free == 1)
	{
		bl_size = get_block_size(alc, bl);
		bud_size = get_block_size(alc, bud);
		if (bud_size == bl_size)
			erase_bud(alc, bl, bud, bl_size);
	}
}

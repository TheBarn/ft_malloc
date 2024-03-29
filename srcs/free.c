/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 09:41:40 by barnout           #+#    #+#             */
/*   Updated: 2018/09/27 17:36:33 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int			get_block_size(t_alloc *alc, void *bl)
{
	t_head	*h;
	int		size;
	int		try_bl_size;
	int		tmp;
	int		offset;

	h = (t_head *)bl;
	size = h->size;
	offset = (int)h->offset;
	try_bl_size = alc->size;
	while (try_bl_size + offset - HEAD_SIZE >= size)
	{
		tmp = try_bl_size;
		try_bl_size /= 2;
	}
	return (tmp + offset);
}

static char	free_big(void *ptr)
{
	int			i;
	void		*bl;
	t_big_head	*h;

	i = 0;
	while (i < g_dib->big_nb)
	{
		bl = (g_dib->big_alc)[i];
		if (bl && ptr == bl + BIG_HEAD_SIZE)
		{
			h = (t_big_head *)bl;
			munmap(bl, h->size + BIG_HEAD_SIZE);
			(g_dib->big_alc)[i] = NULL;
			return (1);
		}
		i++;
	}
	return (0);
}

t_alloc		*find_zone(void *ptr)
{
	t_alloc *alc;
	int		i;

	i = 0;
	while (i < g_dib->tiny_nb)
	{
		alc = (t_alloc *)&((g_dib->tiny_alc)[i]);
		if (ptr >= alc->zn && ptr < alc->zn + alc->size)
			return (alc);
		i++;
	}
	i = 0;
	while (i < g_dib->small_nb)
	{
		alc = (t_alloc *)&((g_dib->small_alc)[i]);
		if (ptr >= alc->zn && ptr < alc->zn + alc->size)
			return (alc);
		i++;
	}
	return (NULL);
}

void		ft_free(void *ptr)
{
	void	*bl;
	t_head	*h;
	t_alloc	*alc;

	if (ptr)
	{
		if (free_big(ptr))
			return ;
		alc = find_zone(ptr);
		bl = ptr - HEAD_SIZE;
		h = (t_head *)bl;
		if (!alc || h->sym != SYM || h->free != 0)
			return ;
		h->free = 1;
		merge_bud(alc, bl);
	}
}

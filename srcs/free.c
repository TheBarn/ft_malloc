/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 09:41:40 by barnout           #+#    #+#             */
/*   Updated: 2018/09/25 18:28:49 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

extern t_dib	*g_dib;

int		get_block_size(t_alloc *alc, void *bl)
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

void	merge_bud(t_alloc *alc, void *bl)
{
	int		bl_size;
	void	*bud;
	t_head	*bh;
	int		bud_size;

	bl_size = get_block_size(alc, bl);
	bud = bl + bl_size;
	bh = (t_head *)bud;
	if (bud < alc->zn + alc->size && bh->sym == SYM && bh->free == 1)
	{
		bud_size = get_block_size(alc, bud);
		ft_memset(bud, TRASH, HEAD_SIZE);
		write_header(bl, 1, bl_size + bud_size - HEAD_SIZE);
		merge_bud(alc, bl);
	}
}

//check if it is correct
t_alloc	*search_big_zone(void *ptr)
{
	int		i;

	i = 0;
	while (i < g_dib->big_nb)
	{
		if (ptr == &((g_dib->big_alc)[i]))
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
//	alc = search_big_zone(ptr);
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
		{
			throw_error("Error: pointer being freed was not allocated\n");
			return ;
		}
		//should be alc->zn, I don't understand this condition
		h->free = 1;
		merge_bud(alc, bl);
//		print_zone(alc, "free", ptr);
	}
}

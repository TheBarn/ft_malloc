/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 09:41:40 by barnout           #+#    #+#             */
/*   Updated: 2018/09/26 17:25:33 by barnout          ###   ########.fr       */
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

void	*find_buddy(t_alloc *alc, void *bl)
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

char	get_side(t_alloc *alc, void *bl, int bl_size)
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

void	merge_bud(t_alloc *alc, void *bl)
{
	void	*bud;
	void	*tmp;
	t_head	*bh;
	int		bud_size;
	int		bl_size;
	char	side;

	bud = find_buddy(alc, bl);
	bh = (t_head *)bud;
	if (bud < alc->zn + alc->size && bud >= alc->zn && bh->sym == SYM && bh->free == 1)
	{
		bl_size = get_block_size(alc, bl);
		bud_size = get_block_size(alc, bud);
		if (bud_size == bl_size)
		{
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
	return (NULL);
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
		ini_dib();
		alc = find_zone(ptr);
		//do nothing if it is the case, maybe put a DEBUG macro
//		print_header(alc);
		bl = ptr - HEAD_SIZE;
		h = (t_head *)bl;
		//same for DEBUG
		if (!alc || h->sym != SYM || h->free != 0)
		{
//			throw_error("Error: pointer being freed was not allocated\n");
			return ;
		}
		//should be alc->zn, I don't understand this condition
		h->free = 1;
		merge_bud(alc, bl);
//		print_zone(alc, "free", ptr);
	}
}

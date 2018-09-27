/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 14:48:26 by barnout           #+#    #+#             */
/*   Updated: 2018/09/27 16:03:53 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	grow_block(t_alloc *alc, void *bl, int mem_size)
{
	int		bl_size;
	int		mock_size;
	void	*bud;
	void	*tmp;
	t_head	*bh;

	bl_size = get_block_size(alc, bl);
	mock_size = bl_size - HEAD_SIZE;
	tmp = bl;
	while (mock_size < mem_size)
	{
		bud = bl + bl_size;
		bh = (t_head *)bud;
		mock_size += get_block_size(alc, bud);
		bl_size = get_block_size(alc, bud);
		ft_memset(bl, TRASH, HEAD_SIZE);
		bl = bud;
	}
	write_header(tmp, 1, 0, mock_size);
	split_block(alc, tmp, mem_size);
	write_header(tmp, 0, 0, mem_size);
}

static char	is_enough_padding_space(t_alloc *alc, void *bl, int mem_size)
{
	int		bl_size;
	int		mock_size;
	int		bud_size;
	void	*bud;
	t_head	*bh;

	bl_size = get_block_size(alc, bl);
	mock_size = bl_size - HEAD_SIZE;
	while (mock_size < mem_size)
	{
		bl_size = get_block_size(alc, bl);
		bud = bl + bl_size;
		if (bud >= alc->zn + alc->size)
			return (0);
		bh = (t_head *)bud;
		if (bh->sym != SYM || bh->free == 0)
			return (0);
		bud_size = get_block_size(alc, bud);
		if (bl_size != bud_size)
			return (0);
		mock_size += bud_size;
		bl = bud;
	}
	return (1);
}

static void	*realloc_block(void *src, int size, t_alloc *alc, void *bl)
{
	int		bl_size;
	void	*ptr;

	bl_size = get_block_size(alc, bl);
	if (size <= bl_size - HEAD_SIZE)
		return (src);
	if (!is_enough_padding_space(alc, bl, size))
	{
		ptr = ft_malloc(size);
		if (!ptr)
			return (NULL);
		ft_memcpy(ptr, src, bl_size - HEAD_SIZE);
		ft_free(src);
		return (ptr);
	}
	grow_block(alc, bl, size);
	return (src);
}

void		*ft_realloc(void *src, size_t size)
{
	void	*bl;
	t_head	*h;
	void	*ptr;
	t_alloc	*alc;

	if (!src)
		return (ft_malloc(size));
	ptr = realloc_big(src, size);
	if (ptr)
		return (ptr);
	alc = find_zone(src);
	bl = src - HEAD_SIZE;
	h = (t_head *)bl;
	if (!alc || h->sym != SYM || h->free != 0)
		return (NULL);
	else
	{
		ptr = realloc_block(src, (int)size, alc, bl);
		return (ptr);
	}
}

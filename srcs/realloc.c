/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 14:48:26 by barnout           #+#    #+#             */
/*   Updated: 2018/09/13 16:42:48 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	grow_block(t_alloc *alc, void *bl, int size)
{
	t_head		*h;
	void		*bud;
	t_head		*bh;

	h = (t_head*)bl;
	while (h->size - HEAD_SIZE < size)
	{
		bud = find_buddy(bl);
		bh = (t_head *)bud;
		erase_buddies(alc, bl, bud);
		bh->sym = 0;
		write_header(alc, bl, 0, h->size * 2);
		print_zone(alc, "grow", 0);
	}
}

char	is_enough_space(t_alloc *alc, void *bl, int size)
{
	void	*bud;
	t_head	*bh;
	int		mock_size;

	mock_size = ((t_head *)bl)->size;
	while (mock_size <= power_of_two(alc->max) / 2)
	{
		bud = xor_size(bl, mock_size);
		if (bud < bl)
			return(0);
		bh = (t_head *)bud;
		if (bh->free != 1 || bh->size != mock_size)
			return (0);
		if (mock_size * 2 - HEAD_SIZE >= size)
			break;
		mock_size *= 2;
	}
	if (mock_size > power_of_two(alc->max) / 2)
		return (0);
	return (1);
}

//TODO size_t
void	*ft_realloc(t_alloc *alc, void *src, int size)
{
	void	*bl;
	t_head	*h;
	void	*ptr;

//TODO check if ptr is in good zone
	bl = src - HEAD_SIZE;
	h = (t_head *)bl;
	if (h->sym != SYM || h->free != 0)
	{
		printf("Error for object %p: pointer being reallocated was not allocated\n", src);
		return(NULL);
	}
	else
	{
		if (size <= h->size - HEAD_SIZE)
			return(src);
		if (!is_enough_space(alc, bl, size))
		{
			ptr = ft_malloc(alc, size);
			ft_memcpy(ptr, src, h->size - HEAD_SIZE);
			ft_free(alc, src);
			return(ptr);
		}
		grow_block(alc, bl, size);
		return(src);
	}
}

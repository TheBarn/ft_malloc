/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 14:48:26 by barnout           #+#    #+#             */
/*   Updated: 2018/09/20 17:17:15 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

extern t_dib	*g_dib;

void	grow_block(t_alloc *alc, void *bl, size_t size)
{
	void		*bud;
	t_head		*bh;
	int			bl_size;

	bl_size = get_block_size(bl);
	while ((size_t)(bl_size - HEAD_SIZE) < size)
	{
		bud = find_buddy(alc, bl);
		bh = (t_head *)bud;
		erase_buddies(alc, bl, bud);
		bh->sym = 0;
		write_header(alc, bl, 0, bl_size * 2);
		print_zone(alc, "realloc", &size);
	}
	write_header(alc, bl, 0, size);
}

char	is_enough_space(t_alloc *alc, void *bl, size_t size)
{
	void	*bud;
	t_head	*bh;
	size_t	mock_size;

	mock_size = get_block_size(bl);
	while (mock_size <= power_of_two(alc->max) / 2)
	{
		bud = find_buddy(alc, bl);
		if (bud < bl)
			return (0);
		bh = (t_head *)bud;
		if (bh->free != 1 || (size_t)get_block_size(bud) != mock_size)
			return (0);
		if (mock_size * 2 - HEAD_SIZE >= size)
			break ;
		mock_size *= 2;
	}
	if (mock_size > power_of_two(alc->max) / 2)
		return (0);
	return (1);
}

void	*realloc_block(void *src, size_t size, t_alloc *alc, void *bl)
{
	int		bl_size;
	void	*ptr;

	bl_size = get_block_size(bl);
	if (size <= (size_t)(bl_size - HEAD_SIZE))
		return (src);
	if (alc == src || !is_enough_space(alc, bl, size))
	{
		ptr = malloc(size);
		ft_memcpy(ptr, src, bl_size - HEAD_SIZE);
		free(src);
		return (ptr);
	}
	grow_block(alc, bl, size);
	return (src);
}

void	*realloc(void *src, size_t size)
{
	void	*bl;
	t_head	*h;
	void	*ptr;
	t_alloc	*alc;

	ft_putstr("\nrealloc: ");
	ft_putptr(src);
	ft_putchar(' ');
	ft_put_size_t(size);
	ft_putchar('\n');
	if (!src)
		return (malloc(size));
	ini_dib();
	ft_putchar('a');
	alc = find_zone(src);
	ft_putchar('b');
	bl = src - HEAD_SIZE;
	h = (t_head *)bl;
	ft_putchar('c');
	if (!alc || h->sym != SYM || h->free != 0)
	{
		throw_error("Error: pointer being reallocated was not allocated\n");
		return (NULL);
	}
	else
	{
		ft_putchar('d');
		ptr = realloc_block(src, size, alc, bl);
		ft_putchar('e');
		return (ptr);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 09:07:14 by barnout           #+#    #+#             */
/*   Updated: 2018/09/26 17:30:58 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_dib *g_dib = NULL;

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
			throw_error("not a block\n");
		if (h->free == 1 && h->size >= mem_size)
			return (bl);
		bl_size = get_block_size(alc, bl);
		i += bl_size;
		bl += bl_size;
	}
	throw_error("no free block\n");
	return (NULL);
}

void	split_block(t_alloc *alc, void *bl, int mem_size)
{
	int		bl_size;
	int		half_av_size;
	t_head	*h;
	void	*bud;

//	ft_putchar('m');
	h = (t_head *)bl;
//	ft_putchar('n');
	bl_size = get_block_size(alc, bl);
//	ft_putchar('o');
	half_av_size = (bl_size / 2) - HEAD_SIZE;
//	ft_putchar('p');
	if (h->size >= mem_size && half_av_size < mem_size)
	{
//		ft_putchar('q');
		write_header(bl, 0, 0, mem_size);
//		ft_putchar('r');
	}
	else
	{
//	ft_putchar('s');
		write_header(bl, 1, 0, half_av_size);
//	ft_putchar('t');
		bud = bl + (bl_size / 2);
//	ft_putchar('u');
		write_header(bud, 1, 1, half_av_size + (bl_size % 2));
//	ft_putchar('v');
		if (bl_size % 2)
			((t_head *)bud)->offset = 1;
//	ft_putchar('w');
		split_block(alc, bl, mem_size);
//	ft_putchar('x');
	}
}

//to verify, it looks terrible
/*
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
*/
void	*malloc(size_t size)
{
	t_alloc *alc;
	void	*bl;

	ft_putstr("malloc: ");
	ft_put_size_t(size);
//	ft_putchar('a');
	ini_dib();
//	ft_putchar('b');
	if (size > SMALL_LIM)
	{
		//	bl = ft_big_malloc(size);
		return (NULL);
	}
//	ft_putchar('c');
	alc = get_alloc_zone((int)size);
//	ft_putchar('d');
	bl = find_block(alc, (int)size);
//	ft_putchar('e');
//	print_zone(alc, "malloc", &size);
	split_block(alc, bl, (int)size);
//	ft_putchar('f');
//	print_zone(alc, "malloc", &size);
	ft_putstr("  return: ");
	ft_putptr(bl + HEAD_SIZE);
	ft_putchar('\n');
//	print_visu(alc);
//	show_dib_state();
	return (bl + HEAD_SIZE);
}

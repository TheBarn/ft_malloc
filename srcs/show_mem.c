/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 17:23:07 by barnout           #+#    #+#             */
/*   Updated: 2018/09/25 18:34:44 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

extern t_dib	*g_dib;

void	ft_putptr_req(size_t ad)
{
	char	d;

	d = ad % 16;
	if (ad > 0)
		ft_putptr_req(ad / 16);
	if (d < 10)
		ft_putchar('0' + d);
	else
		ft_putchar('a' + d - 10);
}

void	ft_putptr(void *ptr)
{
	size_t	ad;

	ad = (size_t)ptr;
	ft_putstr("0x");
	ft_putptr_req(ad);
}

void		print_block_mem(void *bl)
{
	t_head	*h;

	h = (t_head *)bl;
	ft_putptr(bl + HEAD_SIZE);
	ft_putstr(" - ");
	ft_putptr(bl + HEAD_SIZE + h->size - 1);
	ft_putstr(" : ");
	ft_putnbr(h->size);
	ft_putstr(" octets\n");
}

void		print_alc_mem(t_alloc *alc)
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
			throw_error("not a block!!\n");
		if (h->free == 0)
			print_block_mem(bl);
		bl_size = get_block_size(alc, bl);
		i += bl_size;
		bl += bl_size;
	}
}

void		print_alc_header(t_alloc *alc)
{
	if (alc->size == getpagesize() * TINY_PG_MULTI)
		ft_putstr("TINY : ");
	else if (alc->size == getpagesize() * SMALL_PG_MULTI)
		ft_putstr("SMALL : ");
	ft_putptr(alc->zn);
	ft_putchar('\n');
}

t_alloc		*ft_ptr_min(t_alloc *a, t_alloc *b)
{
	if (!a && b)
		return (b);
	if (a && !b)
		return (a);
	if (!a && !b)
		return (NULL);
	if ((void *)a < (void *)b)
		return (a);
	return (b);
}

t_alloc		*next_alloc(void *pr)
{
	int		i;
	t_alloc	*alc;
	t_alloc	*nx;

	i = 0;
	nx = NULL;
	while (i < g_dib->tiny_nb)
	{
		alc = (t_alloc *)&(g_dib->tiny_alc[i++]);
		if ((void *)alc > pr)
			nx = ft_ptr_min(nx, alc);
	}
	i = 0;
	while (i < g_dib->small_nb)
	{
		alc = (t_alloc *)&(g_dib->small_alc[i++]);
		if ((void *)alc > pr)
			nx = ft_ptr_min(nx, alc);
	}
	//special case for big !!
	/*
	i = 0;
	while (i < g_dib->big_nb)
	{
		alc = (t_alloc *)&(g_dib->big_alc[i++]);
		if ((void *)alc > pr)
			nx = ft_ptr_min(nx, alc)
	}
	*/
	return (nx);
}

void	show_alloc_mem()
{
	t_alloc		*alc;

	alc = next_alloc(NULL);
	while (alc)
	{
		print_alc_header(alc);
		print_alc_mem(alc);
		alc = next_alloc(NULL);
	}
}

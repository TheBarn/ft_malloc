/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 17:23:07 by barnout           #+#    #+#             */
/*   Updated: 2018/09/27 15:20:36 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int	print_block_mem(void *bl)
{
	t_head	*h;

	h = (t_head *)bl;
	ft_putptr(bl + HEAD_SIZE);
	ft_putstr(" - ");
	ft_putptr(bl + HEAD_SIZE + h->size - 1);
	ft_putstr(" : ");
	ft_putnbr(h->size);
	ft_putstr(" octets\n");
	return (h->size);
}

static int	print_alc_mem(t_alloc *alc)
{
	void	*bl;
	t_head	*h;
	int		bl_size;
	int		i;
	int		tot;

	bl = alc->zn;
	i = 0;
	tot = 0;
	while (i < alc->size)
	{
		h = (t_head *)bl;
		if (h->sym != SYM)
			break ;
		if (h->free == 0)
			tot += print_block_mem(bl);
		bl_size = get_block_size(alc, bl);
		i += bl_size;
		bl += bl_size;
	}
	return (tot);
}

static void	print_alc_header(t_alloc *alc)
{
	if (alc->size == getpagesize() * TINY_PG_MULTI)
		ft_putstr("TINY : ");
	else if (alc->size == getpagesize() * SMALL_PG_MULTI)
		ft_putstr("SMALL : ");
	ft_putptr(alc->zn);
	ft_putchar('\n');
}

void		ft_show_alloc_mem(void)
{
	t_alloc		*alc;
	size_t		tot;

	tot = 0;
	alc = next_alloc(NULL, &tot);
	while (alc)
	{
		print_alc_header(alc);
		tot += (size_t)print_alc_mem(alc);
		alc = next_alloc((void *)alc, &tot);
	}
	ft_putstr("Total : ");
	ft_put_size_t(tot);
	ft_putstr(" octets for ");
	ft_putnbr(g_dib->nb_pg);
	ft_putstr(" pages\n");
}

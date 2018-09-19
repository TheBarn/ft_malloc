/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 17:23:07 by barnout           #+#    #+#             */
/*   Updated: 2018/09/19 12:12:13 by barnout          ###   ########.fr       */
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

void	show_block(void	*bl)
{
	t_head	*h;
	int		size;

	h = (t_head *)bl;
	if (h->sym == SYM && h->free == 0)
	{
		size = h->size;
		ft_putptr(bl + HEAD_SIZE);
		ft_putstr(" - ");
		ft_putptr(bl + size + HEAD_SIZE);
		ft_putstr(" : ");
		ft_putnbr(size);
		ft_putstr(" octects\n");
	}
}

void	show_alloc(t_alloc *alc)
{
	size_t		len;
	size_t		i;

	len = sum_power_of_two(alc->min, alc->max);
	i = 0;
	while (i < len)
	{
		if ((alc->table)[i])
			show_block((alc->table)[i]);
		i++;
	}
}

void	show_zone(char tiny)
{
	t_alloc		**alc_ar;
	int			nb;
	int			i;

	alc_ar = tiny ? g_dib->tiny_alc : g_dib->small_alc;
	i = 0;
	nb = tiny ? g_dib->tiny_nb : g_dib->small_nb;
	while (i < nb)
		show_alloc(alc_ar[i++]);
}

void	show_large()
{
	int		i;
	int		nb;
	void	*bl;

	i = 0;
	nb = g_dib->big_nb;
	while (i < nb)
	{
		bl = (g_dib->big_alc)[i++];
		show_block(bl);
	}
}

void	show_add(char tiny)
{
	int		i;
	t_alloc	**alc_ar;
	t_alloc	*alc;
	int		nb;

	i = 0;
	alc_ar = tiny ? g_dib->tiny_alc : g_dib->small_alc;
	nb = tiny ? g_dib->tiny_nb : g_dib->small_nb;
	while (i < nb)
	{
		alc = alc_ar[i];
		ft_putchar(' ');
		ft_putptr((void *)alc);
		i++;
	}
}

void	show_alloc_mem()
{
	ft_putstr("TINY:");
	show_add(1);
	ft_putchar('\n');
	show_zone(1);
	ft_putstr("SMALL:");
	show_add(0);
	ft_putchar('\n');
	show_zone(0);
	ft_putstr("LARGE:\n");
	show_large();
	ft_putchar('\n');
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 17:23:07 by barnout           #+#    #+#             */
/*   Updated: 2018/09/20 17:17:56 by barnout          ###   ########.fr       */
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

void	show_block(t_alloc *alc, int ad)
{
	void	*bl;
	t_head	*h;
	int		size;

	bl = get_block(alc, ad);
	h = (t_head *)bl;
	if (h->sym == SYM && h->free == 0)
	{
		size = h->size;
		ft_putptr(bl + HEAD_SIZE);
		ft_putstr(" - ");
		ft_putptr(bl + size + HEAD_SIZE - 1);
		ft_putstr(" : ");
		ft_putnbr(size);
		ft_putstr(" octects\n");
	}
}
/*
void	show_buddies(t_alloc *alc)
{
	size_t	len;
	size_t	i;
	int		ad;

	ft_putstr("BUD:");
	len = sum_power_of_two(0, alc->max - alc->min);
	i = 0;
	while (i < len)
	{
		ad = alc->table[i];
		if (ad == -1)
		{
			ft_putchar(' ');
			ft_putnbr(0);
		}
		else if (ad)
		{
			ft_putchar(' ');
			ft_putnbr(ad);
		}
		i++;
	}
	ft_putchar('\n');
}
*/
int		ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int		get_max_v(t_alloc *alc, size_t len)
{
	int		max_v;
	size_t	i;
	int		ad;

	i = 0;
	max_v = 0;
	while (i < len)
	{
		ad = alc->table[i];
		if (ad)
		{
			if (ad == -1)
				ad = 0;
			max_v = ft_max(max_v, ad);
		}
		i++;
	}
	return (max_v);
}
/*
int		get_max_ad_ind(t_alloc *alc, size_t len, int max_v)
{
	size_t	max_ind;
	size_t	i;
	int		ad;

	i = 0;
	while (i < len)
	{
		ad = alc->table[i];
		if (ad)
		{
			if (ad == -1)
				ad = 0;
			if (ad == mac_v)
				return (i);
		}
		i++;
	}
	return (0);
}
*/
int		get_next_ad(t_alloc *alc, size_t len, int pr)
{
	int		ad;
	size_t	i;
	int		nxt;

	i = 0;
	nxt = power_of_two(alc->max) + 1;
	while (i < len)
	{
		ad = alc->table[i];
		if (ad)
		{
			if (ad > pr && ad < nxt)
				nxt = ad;
		}
		i++;
	}
	return (nxt);
}

void	show_alloc(t_alloc *alc)
{
	size_t		len;
	int			max_v;
	int			ad;

//	show_buddies(alc);
	len = sum_power_of_two(0, alc->max - alc->min);
	max_v = get_max_v(alc, len);
	ad = get_next_ad(alc, len, -2);
	while (ad <= max_v)
	{
		show_block(alc, ad);
		ad = get_next_ad(alc, len, ad);
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
		show_block((t_alloc *)bl, 0); // WRONG!! show_block(bl);
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

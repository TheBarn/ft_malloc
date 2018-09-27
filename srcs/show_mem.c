/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 17:23:07 by barnout           #+#    #+#             */
/*   Updated: 2018/09/27 14:54:49 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		ft_putptr_req(size_t ad)
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

void		ft_putptr(void *ptr)
{
	size_t	ad;

	ad = (size_t)ptr;
	ft_putstr("0x");
	ft_putptr_req(ad);
}

int			print_block_mem(void *bl)
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

int			print_alc_mem(t_alloc *alc)
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

void		print_alc_header(t_alloc *alc)
{
	if (alc->size == getpagesize() * TINY_PG_MULTI)
		ft_putstr("TINY : ");
	else if (alc->size == getpagesize() * SMALL_PG_MULTI)
		ft_putstr("SMALL : ");
	ft_putptr(alc->zn);
	ft_putchar('\n');
}

void		*ft_ptr_min(void *a, void *b)
{
	if (!a && b)
		return (b);
	if (a && !b)
		return (a);
	if (!a && !b)
		return (NULL);
	if (a < b)
		return (a);
	return (b);
}

void		print_big(void *bl, size_t *tot)
{
	size_t	size;

	ft_putstr("LARGE : ");
	ft_putptr(bl);
	ft_putchar('\n');
	ft_putptr(bl + BIG_HEAD_SIZE);
	ft_putstr(" - ");
	size = ((t_big_head *)bl)->size;
	ft_putptr(bl + BIG_HEAD_SIZE + size - 1);
	ft_putstr(" : ");
	ft_put_size_t(size);
	ft_putstr(" octets\n");
	(*tot) += size;
}

void		*get_next_big(void *pr)
{
	int		i;
	void	*min_big;
	void	*bl;

	i = 0;
	min_big = NULL;
	while (i < g_dib->big_nb)
	{
		bl = g_dib->big_alc[i++];
		if (bl > pr)
			min_big = ft_ptr_min(bl, min_big);
	}
	return (min_big);
}

t_alloc		*find_min_alc(t_alloc *ar, int nb, void *pr, void *nx)
{
	int		i;
	t_alloc	*alc;

	i = 0;
	while (i < nb)
	{
		alc = (t_alloc *)&(ar[i++]);
		if ((void *)alc > pr)
			nx = (t_alloc *)ft_ptr_min((void *)nx, (void *)alc);
	}
	return (nx);
}

t_alloc		*next_alloc(void *pr, size_t *tot)
{
	t_alloc	*nx;
	void	*big;

	nx = NULL;
	nx = find_min_alc(g_dib->tiny_alc, g_dib->tiny_nb, pr, nx);
	nx = find_min_alc(g_dib->small_alc, g_dib->small_nb, pr, nx);
	big = get_next_big(pr);
	if (big && big < (void *)nx)
	{
		print_big(big, tot);
		return (next_alloc(big, tot));
	}
	return (nx);
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

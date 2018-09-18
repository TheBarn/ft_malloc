/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 09:41:40 by barnout           #+#    #+#             */
/*   Updated: 2018/09/18 17:54:07 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

extern t_dib	*g_dib;

void	erase_buddies(t_alloc *alc, void *bl, void *bud)
{
	int		s;
	int		ind;
	int		len;
	int		i;
	int		j;

	ind = power_of_two_ind(((t_head *)bl)->size);
	s = find_seq_start(alc, ind);
	len = power_of_two(alc->max - ind);
	i = 0;
	j = 0;
	while (i < len)
	{
		if ((alc->table)[s + i] == bl || (alc->table)[s + i] == bud)
		{
			(alc->table)[s + i] = NULL;
			j++;
		}
		if (j == 2)
			break ;
		i++;
	}
}

int		merge_bud(t_alloc *alc, void *bl)
{
	void	*bud;
	t_head	*h;
	t_head	*bh;
	int		size;

	h = (t_head*)bl;
	size = h->size;
	if ((size_t)size == power_of_two(alc->max))
		return (0);
	bud = find_buddy(bl);
	bh = (t_head*)bud;
	if (bh && bh->sym == SYM && size == bh->size && bh->free == 1)
	{
		erase_buddies(alc, bl, bud);
		if (bud < bl)
			bl = bud;
		bh->sym = 0;
		write_header(alc, bl, 1, 2 * h->size);
		if (alc->left < 2 * h->size)
			alc->left = 2 * h->size;
		print_zone(alc, "free", NULL);
		merge_bud(alc, bl);
	}
	return (0);
}

t_alloc	*search_big_zone(void *ptr)
{
	int		i;

	i = 0;
	while (i < g_dib->big_nb)
	{
		if (ptr == (g_dib->big_alc)[i])
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
	ft_putchar('k');
	ft_putnbr(g_dib->tiny_nb);
	while (i < g_dib->tiny_nb)
	{
		ft_putchar('l');
		alc = (g_dib->tiny_alc)[i];
		ft_putchar('m');
		if (ptr >= alc->zn && ptr < alc->zn + power_of_two(alc->max))
			return (alc);
		ft_putchar('n');
		i++;
	}
	i = 0;
	while (i < g_dib->small_nb)
	{
		alc = (g_dib->small_alc)[i];
		if (ptr >= alc->zn && ptr < alc->zn + power_of_two(alc->max))
			return (alc);
		i++;
	}
	alc = search_big_zone(ptr);
	return (alc);
}

void	free(void *ptr)
{
	void	*bl;
	t_head	*h;
	t_alloc	*alc;

	show_alloc_mem();
	ft_putstr("\nfree: ");
	ft_put_size_t((size_t)ptr);
	ft_putchar('\n');
	if (ptr)
	{
		ft_putchar('a');
		ini_dib();
		alc = find_zone(ptr);
		if (!alc)
		{
			throw_error("Error: pointer being freed was not allocated\n");
			return ;
		}
		ft_putchar('?');
		print_header(alc);
		ft_putchar('b');
		bl = ptr - HEAD_SIZE;
		h = (t_head *)bl;
		ft_putchar('c');
		ft_put_size_t((size_t)alc);
		ft_putchar(' ');
		ft_putchar(h->sym);
		ft_putnbr(h->free);
		if (h->sym != SYM || h->free != 0)
			throw_error("Error: pointer being freed was not allocated\n");
		else if (alc != ptr)
		{
			ft_putchar('d');
			h->free = 1;
			merge_bud(alc, bl);
			print_zone(alc, "free", ptr);
			ft_putchar('e');
		}
	}
}

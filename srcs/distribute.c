/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distribute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 09:40:07 by barnout           #+#    #+#             */
/*   Updated: 2018/09/26 17:01:14 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

extern t_dib	*g_dib;

int		ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

void	ini_alloc(t_alloc *alc, char tiny)
{
	int		multi;

	multi = tiny ? TINY_PG_MULTI : SMALL_PG_MULTI;
	alc->size = getpagesize() * multi;
	alc->left = alc->size - HEAD_SIZE;
	alc->zn = ft_mmap(alc->size);
	write_header(alc->zn, 1, 0, alc->size - HEAD_SIZE);
}

t_alloc		*make_new_zone(char tiny)
{
	int		nb;
	t_alloc	*ar;
	t_alloc	*alc;

	nb = tiny ? g_dib->tiny_nb : g_dib->small_nb;
	if (!is_enough_dib_left(nb))
		double_dib_size();
	ar = tiny ? g_dib->tiny_alc : g_dib->small_alc;
	alc = (t_alloc *)(&(ar[nb]));
	if (tiny)
		g_dib->tiny_nb += 1;
	else
		g_dib->small_nb += 1;
	ini_alloc(alc, tiny);
	return (alc);
}

char		is_enough_mem_left(t_alloc *alc, int mem_size)
{
	int		i;
	void	*bl;
	t_head	*h;
	int		bl_size;

	if (alc->left < mem_size)
		return (0);
	bl = alc->zn;
	i = 0;
	while (i < alc->size)
	{
		h = (t_head *)bl;
		if (h->sym != SYM)
			throw_error("ho ho\n");
		if (h->free == 1 && h->size >= mem_size)
			return (1);
		bl_size = get_block_size(alc, bl);
		i += bl_size;
		bl += bl_size;
	}
	alc->left = ft_min(alc->left, mem_size);
	return (0);
}

t_alloc		*get_zone(int size, char tiny)
{
	t_alloc		*ar;
	t_alloc		*alc;
	int			i;
	int			nb;

	nb = tiny ? g_dib->tiny_nb : g_dib->small_nb;
	ar = tiny ? g_dib->tiny_alc : g_dib->small_alc;
	if (!nb)
	{
		alc = make_new_zone(tiny);
		return (alc);
	}
	else
	{
		i = 0;
		while (i < nb)
		{
			alc = &(ar[i]);
			if (is_enough_mem_left(alc, size))
				return (alc);
			i++;
		}
		alc = make_new_zone(tiny);
		return (alc);
	}
}

t_alloc		*get_alloc_zone(int size)
{
	if (size <= 0 || size > SMALL_LIM)
		return (NULL);
	if (size <= TINY_LIM)
	{
		return (get_zone(size, 1));
	}
	else
	{
		return (get_zone(size, 0));
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distribute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 09:40:07 by barnout           #+#    #+#             */
/*   Updated: 2018/09/18 16:51:55 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

extern t_dib	*g_dib;

void		add_to_dib(t_alloc *alc, char tiny)
{
	int			nb;
	t_alloc		**ar;

	nb = tiny ? g_dib->tiny_nb : g_dib->small_nb;
	ar = tiny ? g_dib->tiny_alc : g_dib->small_alc;
	if (nb > \
		(getpagesize() - ((int)sizeof(t_dib)) / 3) / (int)sizeof(t_alloc *))
		double_dib_size();
	ar[nb] = alc;
	if (tiny)
		g_dib->tiny_nb += 1;
	else
		g_dib->small_nb += 1;
}

t_alloc		*make_new_zone(char tiny)
{
	t_alloc		*alc;
	int			min;
	int			max;

	min = tiny ? TINY_MIN : SMALL_MIN;
	max = tiny ? TINY_MAX : SMALL_MAX;
	alc = make_alloc(min, max);
	add_to_dib(alc, tiny);
	print_header(alc);
	return (alc);
}

t_alloc		*get_zone(size_t size, char tiny)
{
	t_alloc		**ar;
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
			alc = ar[i];
			if ((size_t)alc->left >= size)
				return (alc);
			i++;
		}
		alc = make_new_zone(tiny);
		return (alc);
	}
}

t_alloc		*get_alloc_zone(size_t size)
{
	ft_putchar('?');
	if (size <= 0 || size > power_of_two(SMALL_MAX) / 100 - HEAD_SIZE)
		return (NULL);
	if (size <= power_of_two(TINY_MAX) / 100 - HEAD_SIZE)
		return (get_zone(size, 1));
	if (size <= power_of_two(SMALL_MAX) / 100 - HEAD_SIZE)
		return (get_zone(size, 0));
	return (NULL);
}

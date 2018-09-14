/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distribute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 09:40:07 by barnout           #+#    #+#             */
/*   Updated: 2018/09/14 14:57:29 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		add_to_dib(t_dib *dib, t_alloc *alc, char tiny)
{
	int			nb;
	t_alloc		**ar;

	nb = tiny ? dib->tiny_nb : dib->small_nb;
	ar = tiny ? dib->tiny_alc : dib->small_alc;
	if (nb > (getpagesize() - ((int)sizeof(t_dib)) / 3) / (int)sizeof(t_alloc *))
		dib = double_dib_size(dib);
	ar[nb] = alc;
	if (tiny)
		dib->tiny_nb += 1;
	else
		dib->small_nb += 1;
}

t_alloc		*make_new_zone(t_dib *dib, char tiny)
{
	t_alloc		*alc;
	int			min;
	int			max;

	min = tiny ? TINY_MIN : SMALL_MIN;
	max = tiny ? TINY_MAX : SMALL_MAX;
	alc = make_alloc(min, max);
	add_to_dib(dib, alc, tiny);
	return (alc);
}

t_alloc		*get_zone(t_dib *dib, int size, char tiny)
{
	t_alloc		**ar;
	t_alloc		*alc;
	int			i;
	int			nb;

	nb = tiny ? dib->tiny_nb : dib->small_nb;
	ar = tiny ? dib->tiny_alc : dib->small_alc;
	if (!nb)
	{
		alc = make_new_zone(dib, tiny);
		return (alc);
	}
	else
	{
		i = 0;
		while (i < nb)
		{
			alc = ar[i];
//TODO update left with size of bigget block left
			if (alc->left >= size)
				return (alc);
			i++;
		}
		alc = make_new_zone(dib, tiny);
		return (alc);
	}
}

t_alloc		*get_alloc_zone(t_dib *dib, int size)
{
	if (size <= 0 || size > SMALL_LIM)
		return (NULL);
	if (size <= TINY_LIM)
		return (get_zone(dib, size, 1));
	if (size <= SMALL_LIM)
		return (get_zone(dib, size, 0));
	return (NULL);
}

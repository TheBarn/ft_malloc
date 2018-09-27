/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_next.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 15:04:43 by barnout           #+#    #+#             */
/*   Updated: 2018/09/27 17:03:48 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		*ft_ptr_min(void *a, void *b)
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

static void		print_big(void *bl, size_t *tot)
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

static void		*get_next_big(void *pr)
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

static t_alloc	*find_min_alc(t_alloc *ar, int nb, void *pr, void *nx)
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

t_alloc			*next_alloc(void *pr, size_t *tot)
{
	t_alloc	*nx;
	void	*big;

	nx = NULL;
	nx = find_min_alc(g_dib->tiny_alc, g_dib->tiny_nb, pr, nx);
	nx = find_min_alc(g_dib->small_alc, g_dib->small_nb, pr, nx);
	big = get_next_big(pr);
	if (big && (!nx || big < (void *)nx))
	{
		print_big(big, tot);
		return (next_alloc(big, tot));
	}
	return (nx);
}

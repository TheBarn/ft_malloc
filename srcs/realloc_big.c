/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_big.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 15:09:34 by barnout           #+#    #+#             */
/*   Updated: 2018/09/27 16:01:34 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int		get_page_multi(size_t size)
{
	int		multi;
	int		pg_size;

	multi = 1;
	pg_size = getpagesize();
	while ((size_t)(multi * pg_size) < size)
		multi++;
	return (multi);
}

void	*new_big_malloc(void *src, size_t size, size_t old_size)
{
	void	*ptr;

	ptr = ft_malloc(size);
	if (!ptr)
		return (NULL);
	ft_memcpy(ptr, src, old_size);
	return (ptr);
}

void	*realloc_big(void *src, size_t size)
{
	int			i;
	void		*bl;
	t_big_head	*h;
	int			multi;

	i = 0;
	while (i < g_dib->big_nb)
	{
		bl = (g_dib->big_alc)[i];
		if (bl && bl + BIG_HEAD_SIZE == src)
		{
			h = (t_big_head *)bl;
			if (size <= h->size)
				return (src);
			multi = get_page_multi(h->size + BIG_HEAD_SIZE);
			if (size + BIG_HEAD_SIZE <= (size_t)(multi * getpagesize()))
				return (src);
			return (new_big_malloc(src, size, h->size));
		}
		i++;
	}
	return (NULL);
}

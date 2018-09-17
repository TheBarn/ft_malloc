/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 11:46:16 by barnout           #+#    #+#             */
/*   Updated: 2018/09/17 14:40:22 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

extern t_dib	*g_dib;

void		copy_dib_value(t_dib *new_dib, int size, int offset)
{
	ft_memcpy(new_dib->tiny_alc, g_dib->tiny_alc, (size / 2 - offset) / 3);
	ft_memcpy(new_dib->small_alc, g_dib->small_alc, (size / 2 - offset) / 3);
	ft_memcpy(new_dib->big_alc, g_dib->big_alc, (size / 2 - offset) / 3);
}

void		double_dib_size(void)
{
	void	*pg;
	int		size;
	int		offset;
	int		left;
	t_dib	*new_dib;

	size = getpagesize() * g_dib->size * 2;
	pg = mmap(NULL, size, PROT_READ | PROT_WRITE, \
			MAP_ANON | MAP_PRIVATE, -1, 0);
	if (!pg)
		throw_error("Error: mmap allocation: no space found\n");
	new_dib = (t_dib *)pg;
	offset = (int)sizeof(t_dib);
	left = size - offset;
	new_dib->tiny_alc = (t_alloc **)(&pg[offset]);
	new_dib->small_alc = (t_alloc **)(&pg[offset + left / 3]);
	new_dib->big_alc = (void **)(&pg[offset + (left / 3) * 2]);
	new_dib->tiny_nb = g_dib->tiny_nb;
	new_dib->small_nb = g_dib->small_nb;
	new_dib->big_nb = g_dib->big_nb;
	new_dib->size = g_dib->size * 2;
	if (munmap(g_dib, (size / 2)) == -1)
		throw_error("Error: could not unmap\n");
	g_dib = new_dib;
}

void		ini_dib(void)
{
	void	*pg;
	t_dib	*dib;
	int		left;
	int		offset;

	pg = mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE, \
				MAP_ANON | MAP_PRIVATE, -1, 0);
	if (!pg)
		throw_error("Error: mmap allocation: no space found\n");
	dib = (t_dib *)pg;
	offset = (int)sizeof(t_dib);
	left = getpagesize() - offset;
	dib->tiny_alc = (t_alloc **)(&pg[offset]);
	dib->small_alc = (t_alloc **)(&pg[offset + left / 3]);
	dib->big_alc = (void **)(&pg[offset + (left / 3) * 2]);
	dib->tiny_nb = 0;
	dib->small_nb = 0;
	dib->big_nb = 0;
	dib->size = 1;
	g_dib = dib;
	print_header(NULL);
}

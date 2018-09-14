/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 11:46:16 by barnout           #+#    #+#             */
/*   Updated: 2018/09/14 15:46:00 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_dib		*double_dib_size(t_dib *dib)
{
	void	*pg;
	int		size;
	int		offset;
	int		left;
	t_dib	*new_dib;

	size = getpagesize() * dib->size * 2;
	pg = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (!pg)
		printf("Error: mmap allocation of size %d: no space found\n", size);
	new_dib = (t_dib *)pg;
	offset = (int)sizeof(t_dib);
	left = size - offset;
	new_dib->tiny_alc = (t_alloc **)(&pg[offset]);
	new_dib->small_alc = (t_alloc **)(&pg[offset + left / 3]);
	new_dib->big_alc = (void **)(&pg[offset + (left / 3) * 2]);
	ft_memcpy(new_dib->tiny_alc, dib->tiny_alc, (size / 2 - offset) / 3);
	ft_memcpy(new_dib->small_alc, dib->small_alc, (size / 2 - offset) / 3);
	ft_memcpy(new_dib->big_alc, dib->big_alc, (size / 2 - offset) / 3);
	new_dib->tiny_nb = dib->tiny_nb;
	new_dib->small_nb = dib->small_nb;
	new_dib->big_nb = dib->big_nb;
	new_dib->size = dib->size * 2;
	if (munmap(dib, (size / 2)) == -1)
		printf("Error: could not unmap object %p\n", dib);
	return (new_dib);
}

t_dib		*ini_dib(void)
{
	void	*pg;
	t_dib	*dib;
	int		left;
	int		offset;

	pg = mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (!pg)
		printf("Error: mmap allocation of size %d: no space found\n", getpagesize());
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
	printf("\033[2J");
	print_header(dib, NULL);
	return (dib);
}

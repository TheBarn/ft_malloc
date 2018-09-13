/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 09:41:40 by barnout           #+#    #+#             */
/*   Updated: 2018/09/13 11:05:21 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	erase_buddies(t_alloc *alc, void *bl, void *bud)
{
	t_head	*h;
	int		size;
	int		s;
	int		ind;
	int		len;
	int		i;
	int		j;

	h = (t_head *)bl;
	size = h->size;
	ind = power_of_two_ind(size);
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
			break;
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
	if (size == power_of_two(alc->max))
		return(0);
	bud = find_buddy(bl);
	bh = (t_head*)bud;
	if (bh && bh->sym == SYM && size == bh->size && bh->free == 1)
	{
		erase_buddies(alc, bl, bud);
		bh->sym = 0;
		write_header(alc, bl, 1, 2 * h->size);
		merge_bud(alc, bl);
	}
	return(0);
}

void	ft_free(t_alloc *alc, void *ptr)
{
	void	*bl;
	t_head	*h;

	bl = xor_size(ptr, HEAD_SIZE);
	h = (t_head *)bl;
	if (h->sym != SYM)
		printf("This is sick...\n");
	if (h->free != 0)
		printf("wtf you have already freed this block!\n");
	h->free = 1;
	merge_bud(alc, bl);
}

int		main()
{
	t_alloc		*alc;
	void		*ptr;

	alc = ini_alloc();
	ptr = ft_malloc(alc, 500);
	dump_table(alc);
	return(0);
}

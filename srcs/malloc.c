/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 09:07:14 by barnout           #+#    #+#             */
/*   Updated: 2018/09/14 15:09:58 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

//TODO manage which zone to use according to size of malloc
int		find_fit(t_alloc *alc, int size)
{
	int		fit;

	fit = alc->min;
	while (power_of_two(fit) - HEAD_SIZE < size && fit < alc->max)
		fit++;
	return (fit);
}

int		find_block_index(t_alloc *alc, int fit)
{
	int		s;
	int		len;
	int		i;
	t_head	*h;
	void	*bl;

	s = find_seq_start(alc, fit);
	i = 0;
	len = sum_power_of_two(0, alc->max - fit);
	bl = NULL;
	while (i < len)
	{
		if (alc->table[s + i])
		{
			h = (t_head *)(alc->table[s + i]);
			if (h->free == 1)
			{
				bl = alc->table[s + i];
				break;
			}
		}
		i++;
	}
	if (bl == NULL)
	{
		alc->left = power_of_two(fit - 1);
		return (-1);
	}
	return(s + i);
}

void	*xor_size(void *ptr, int size)
{
	return((void *)((uintptr_t)ptr ^ size));
}

void	*find_buddy(void *bl)
{
	void	 	*bud;
	t_head		*h;

	h = (t_head *)bl;
	bud = xor_size(bl, h->size);
	return (bud);
}

void	*split_block(t_alloc *alc, int ind, int fit)
{
	void	*bl;
	int		bl_size;
	void	*bud;

	bl = alc->table[ind];
	bl_size = ((t_head *)bl)->size;
	if (fit == power_of_two_ind(bl_size))
	{
		((t_head *)bl)->free = 0;
		return (bl);
	}
	alc->table[ind] = NULL;
	ind = write_header(alc, bl, 1, bl_size / 2);
	bud = find_buddy(bl);
	write_header(alc, bud, 1, bl_size / 2);
	print_zone(alc, "Malloc");
	bl = split_block(alc, ind, fit);
	return (bl);
}

//TODO  munmap
//TODO	size_t
void	*ft_malloc(t_dib *dib, int size)
{
	t_alloc *alc;
	int		fit;
	int		ind;
	void	*bl;

	if (size > SMALL_LIM)
	{
		bl = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		if (!bl)
			printf("Error: mmap allocation of size %d: no space found\n", size);
		if (dib->big_nb >= (getpagesize() - ((int)sizeof(t_dib)) / 3) / (int)sizeof(t_alloc *))
			dib = double_dib_size(dib);
		(dib->big_alc)[dib->big_nb] = bl;
		dib->big_nb += 1;
		return (bl);
	}
	ind = -1;
	while (ind < 0)
	{
		alc = get_alloc_zone(dib, size);
		fit = find_fit(alc, size);
		ind = find_block_index(alc, fit);
	}
	bl = split_block(alc, ind, fit);
	print_zone(alc, "Malloc");
	return (bl + HEAD_SIZE);
}

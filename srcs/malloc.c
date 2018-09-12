/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 09:07:14 by barnout           #+#    #+#             */
/*   Updated: 2018/09/12 18:46:59 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int		find_fit(t_alloc *alc, int size)
{
	int		fit;

	fit = alc->min;
	while (power_of_two(fit) - HEAD_SIZE < size && fit < alc->max)
		fit++;
	if (power_of_two(fit) - HEAD_SIZE < size)
		printf("Grr zone not big enough\n");
	return (fit);
}

//make first always there?
int		find_block_index(t_alloc *alc, int fit)
{
	int		s;
	int		len;
	int		i;
	t_head	*h;
	void	*bl;

	s = find_seq_start(alc, fit);
	i = 0;
	len = sum_power_of_two(0, fit);
	dump_table(alc);
	bl = NULL;
	while (i < len)
	{
		if (alc->table[s + i])
		{
			h = (t_head *)(alc->table[s + i]);
			//find better place for checks
			if (h->sym != SYM)
				printf("What are you doing?\n");
			if (h->free == 1)
			{
				bl = alc->table[s + i];
				break;
			}
		}
		i++;
	}
	if (bl == NULL)
		printf("oh no, no block avalaible\n");
	return(s + i);
}

void	*find_buddy(void *bl)
{
	uintptr_t 	bud;
	t_head		*h;

	h = (t_head *)bl;
	bud = (uintptr_t)h ^ h->size;
	return ((void *)bud);
}

// do I really need to store free and sym?
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
	bl = split_block(alc, ind, fit);
	return (bl);
}

//TODO	size_t
void	*ft_malloc(t_alloc *g_alc, int size)
{
	t_alloc *alc;
	int		fit;
	int		ind;
	void	*bl;

	if (size < power_of_two(10))
		alc = &(g_alc[0]);
	else
		alc = &(g_alc[1]);
	fit = find_fit(alc, size);
	ind = find_block_index(alc, fit);
	bl = split_block(alc, ind, fit);
	return (bl);
}

int		main()
{
	t_alloc		*alc;
	alc = ini_alloc();
	ft_malloc(alc, 500);
	ft_malloc(alc, 32);
	dump_table(&(alc[0]));
	return(0);
}

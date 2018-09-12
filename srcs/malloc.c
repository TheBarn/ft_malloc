/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 09:07:14 by barnout           #+#    #+#             */
/*   Updated: 2018/09/12 16:50:36 by barnout          ###   ########.fr       */
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
void	*find_available_block(t_alloc *alc, int fit)
{
	int		s;
	int		len;
	int		i;
	t_head	*h;
	void	*bl;

	s = find_seq_start(alc, fit);
	i = 0;
	len = sum_power_of_two(0, fit);
	bl = NULL;
	while (i < len)
	{
		if (alc->table[s + i])
		{
			h = (t_head *)(alc->table[s + i]);
			if (h->sym != SYM)
				printf("What are you doing?\n");
			if (h->free == 1)
				bl = alc->table[s + i];
				break;
		}
		i++;
	}
	if (bl == NULL)
		printf("oh no, no block avalaible");
	return(bl);
}

void	*find_block(t_alloc *alc, int fit)
{
	void	*bl;

	bl = find_available_block(alc, fit);
	printf("BLOCK %p\n", bl);
	return (bl);
}

//TODO	size_t
void	*ft_malloc(t_alloc *g_alc, int size)
{
	t_alloc *alc;
	int		fit;
	void	*bl;

	if (size < power_of_two(10))
		alc = &(g_alc[0]);
	else
		alc = &(g_alc[1]);
	fit = find_fit(alc, size);
	bl = find_block(alc, fit);
	return (bl);
}

int		main()
{
	t_alloc		*alc;
	alc = ini_alloc();
	dump_table(&(alc[0]));
	ft_malloc(alc, 500);
	return(0);
}

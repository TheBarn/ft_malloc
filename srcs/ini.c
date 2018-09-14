/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ini.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 15:58:31 by barnout           #+#    #+#             */
/*   Updated: 2018/09/14 15:03:53 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int		find_seq_start(t_alloc *alc, int ind)
{
	int		s;

	s = sum_power_of_two(alc->max - ind + 1, alc->max - alc->min);
	return(s);
}

int		write_header_in_table(t_alloc *alc, void *bl, int bl_size)
{
	int		s;
	int		i;
	int		len;
	int		ind;

	ind = power_of_two_ind(bl_size);
	s = find_seq_start(alc, ind);
	i = 0;
	len = power_of_two(alc->max - ind);
	while (i < len && (alc->table)[s + i] != NULL)
		i++;
	alc->table[s + i] = bl;
	return (s + i);
}


int		write_header(t_alloc *alc, void *bl, char fr, int bl_size)
{
	int		ind;

	((t_head *)bl)->sym = SYM;
	((t_head *)bl)->free = fr;
	((t_head *)bl)->size = bl_size;
	ind = write_header_in_table(alc, bl, bl_size);
	return (ind);
}

void	*get_new_zone(int zn_size)
{
	void	*zn;

	zn = mmap(NULL, zn_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (!zn)
		printf("Error: mmap allocation of size %d: no space found\n", zn_size);
	return(zn);
}

void	*make_table(t_alloc *alc)
{
	int		ind;
	int		nb;
	int		size;
	void	**table;

	ind = alc->max;
	nb = sum_power_of_two(alc->min, ind);
	size = nb * (int)sizeof(void *);
	table = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (!table)
	{
		printf("Error: mmap allocation of size %d: no space found\n", size);
		return(NULL);
	}
	memset(table, 0, size);
	return(table);
}

t_alloc		*make_alloc(int min, int max)
{
	t_alloc	*alc;
	void    *zn;
	int     zn_size;

	alc = (t_alloc *)mmap(NULL, sizeof(t_alloc), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (!alc)
	{
		printf("Error: mmap allocation of size %lu: no space found\n", sizeof(t_alloc));
		return(NULL);
	}
	alc->min = min;
	alc->max = max;
	//TODO multiple of getpagesize()
	zn_size = power_of_two(max);
	alc->left = zn_size - HEAD_SIZE;
	zn = get_new_zone(zn_size);
	if (!zn)
		return(NULL);
	alc->zn = zn;
	alc->table = make_table(alc);
	if (!alc->table)
		return(NULL);
	write_header(alc, zn, 1, zn_size);
	return(alc);
}

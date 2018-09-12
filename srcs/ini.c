/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ini.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 15:58:31 by barnout           #+#    #+#             */
/*   Updated: 2018/09/12 18:01:01 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int		find_seq_start(t_alloc *alc, int bl_size)
{
	int		ind;
	int		s;

	ind = power_of_two_ind(bl_size);
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
	s = find_seq_start(alc, bl_size);
	i = 0;
	len = power_of_two(alc->max - ind);
	while (i < len && (alc->table)[s + i] != NULL)
		i++;
	if (i == len)
		printf("OMG no memory left\n");
	alc->table[s + i] = bl;
	return (s + i);
}


int		write_header(t_alloc *alc, void *bl, char fr, int bl_size)
{
	int		ind;

	if (!bl || bl_size < (int)sizeof(t_head))
		printf("ho ho !\n");
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
		printf("adios amigos\n");
	return(zn);
}

void	make_table(t_alloc *alc)
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
		printf("zut!\n");
	memset(table, 0, size);
	alc->table = table;
}

void		make_alloc(t_alloc *alc, int min, int max)
{
	void    *zn;
	int     zn_size;

	alc->min = min;
	alc->max = max;
	//TODO multiple of getpagesize()
	zn_size = power_of_two(max);
	zn = get_new_zone(zn_size);
	alc->zn = zn;
	make_table(alc);
	write_header(alc, zn, 1, zn_size);
}

t_alloc		*ini_alloc(void)
{
	t_alloc		*alc;

	alc = mmap(NULL, sizeof(t_alloc *) * 2, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	make_alloc(&(alc[0]), TINY_MIN, TINY_MAX);
	make_alloc(&(alc[1]), SMALL_MIN, SMALL_MAX);
	return (alc);
}

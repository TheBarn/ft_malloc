/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 09:07:14 by barnout           #+#    #+#             */
/*   Updated: 2018/09/12 15:45:09 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	write_header_in_table(t_alloc *alc, void *bl, int bl_size)
{
	int		ind;
	int		s;
	int		i;
	int		len;

	ind = power_of_two_ind(bl_size);
	s = sum_power_of_two(alc->max - ind + 1, alc->max - alc->min);
	i = 0;
	len = power_of_two(alc->max - ind);
	while (i < len && (alc->table)[s + i] != NULL)
		i++;
	if (i == len)
		printf("OMG no memory left\n");
	alc->table[s + i] = bl;
	printf("IND: %d\n", s + i);
	printf("PTR: %p\n", alc->table[s + i]);
}


void	write_header(t_alloc *alc, void *bl, char fr, int bl_size)
{
	if (!bl || bl_size < (int)sizeof(t_head))
		printf("ho ho !\n");
	((t_head *)bl)->sym = '*';
	((t_head *)bl)->free = fr;
	((t_head *)bl)->size = bl_size;
	write_header_in_table(alc, bl, bl_size);
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
	printf("table size: %d\n", size);
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
	printf("zone_size: %d\n", zn_size);
	zn = get_new_zone(zn_size);
	alc->zn = zn;
	make_table(alc);
	write_header(alc, zn, 1, zn_size);
	dump_table(alc);
}

void	ini_alloc()
{
	t_alloc		alc[2];

	make_alloc(&(alc[0]), TINY_MIN, TINY_MAX);
//	make_alloc(&(alc[1]), SMALL_MIN, SMALL_MAX);
}

int		main()
{
	ini_alloc();
	return(0);
}

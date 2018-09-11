/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 09:07:14 by barnout           #+#    #+#             */
/*   Updated: 2018/09/11 16:50:13 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	write_header(void **table, void *bl, char fr, int bl_size)
{
	int		ind;
	int		s;

	if (!bl || bl_size < (int)sizeof(t_head))
		printf("ho ho !\n");
	((t_head *)bl)->sym = '*';
	((t_head *)bl)->free = fr;
	((t_head *)bl)->size = bl_size;
	ind = power_of_two_ind(bl_size);
	s = sum_power_of_two(4, ind);
	printf("HEY %d\n", s-1);
	table[s - 1] = (void *)0xFFFFFFFFFFFFFFFF;
	print_mem((char *)table, s * (int)sizeof(void *));
}


void	*get_new_zone(int zn_size)
{
	void	*zn;

	zn = mmap(NULL, zn_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (!zn)
		printf("adios amigos\n");
	return(zn);
}

void	*make_table(int zn_size)
{
	int		ind;
	int		nb;
	int		size;
	void	**table;

	ind = power_of_two_ind(zn_size);
	nb = sum_power_of_two(4, ind);
	size = nb * (int)sizeof(void *);
	printf("table size: %d\n", size);
	table = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (!table)
		printf("zut!\n");
	memset(table, 0, size);
	return(table);
}

void	ini_alloc(int pow)
{
	void    *zn;
	int     zn_size;
	void	*table;

	zn_size = getpagesize() * power_of_two(pow);
	printf("zone_size: %d\n", zn_size);
	zn = get_new_zone(zn_size);
	table = make_table(zn_size);
	write_header(table, zn, 1, zn_size);
	printf("block_size: %d\n", ((t_head *)zn)->size);
	printf("free %hhd\n", ((t_head *)zn)->free);
	printf("%c\n", ((char *)zn)[0]);
	printf("%d\n", power_of_two_ind(zn_size));
}

int		main()
{
	ini_alloc(0);
	return(0);
}

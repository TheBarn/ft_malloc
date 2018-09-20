/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ini.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 15:58:31 by barnout           #+#    #+#             */
/*   Updated: 2018/09/20 15:47:46 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int		find_seq_start(t_alloc *alc, int ind)
{
	int		s;

	s = sum_power_of_two(0, alc->max - ind - 1);
	return (s);
}

int		write_header_in_table(t_alloc *alc, int ad, int bl_size)
{
	int		s;
	int		i;
	int		len;
	int		ind;

	ind = power_of_two_ind(bl_size);
	s = find_seq_start(alc, ind);
	i = 0;
	len = power_of_two(alc->max - ind);
	while (i < len && (alc->table)[s + i] != 0)
		i++;
	if (ad)
		alc->table[s + i] = ad;
	else
		alc->table[s + i] = -1;
	return (s + i);
}

int		write_header(t_alloc *alc, void *bl, char fr, int size)
{
	int		ind;
	int		ad;
	int		bl_size;

	bl_size = sup_power_of_two(size);
	((t_head *)bl)->sym = SYM;
	((t_head *)bl)->free = fr;
	((t_head *)bl)->size = size;
	ad = get_ad(alc, bl);
	ind = write_header_in_table(alc, ad, bl_size);
	return (ind);
}

void	*get_new_zone(int zn_size)
{
	void	*zn;

	zn = mmap(NULL, zn_size, PROT_READ | PROT_WRITE, \
								MAP_ANON | MAP_PRIVATE, -1, 0);
	if (!zn)
		throw_error("Error: mmap allocation: no space found\n");
	return (zn);
}

int		*make_table(t_alloc *alc)
{
	size_t	nb;
	size_t	size;
	int		*table;

	nb = sum_power_of_two(0, alc->max - alc->min);
	size = nb * (int)sizeof(int);
	table = (int *)mmap(NULL, size, PROT_READ | PROT_WRITE,				\
										MAP_ANON | MAP_PRIVATE, -1, 0);
	if (!table)
	{
		throw_error("Error: mmap allocation: no space found\n");
		return (NULL);
	}
//TEST if zero filled
//	memset(table, 0, size);
	return (table);
}

//TODO norme on libft
t_alloc	*make_alloc(int min, int max)
{
	t_alloc	*alc;
	void	*zn;
	int		zn_size;

	alc = (t_alloc *)mmap(NULL, sizeof(t_alloc), PROT_READ | PROT_WRITE, \
											MAP_ANON | MAP_PRIVATE, -1, 0);
	if (!alc)
	{
		throw_error("Error: mmap allocation: no space found\n");
		return (NULL);
	}
	alc->min = min;
	alc->max = max;
	//TODO multiple of getpagesize()
	zn_size = power_of_two(max);
	alc->left = zn_size - HEAD_SIZE;
	zn = get_new_zone(zn_size);
	if (!zn)
		return (NULL);
	alc->zn = zn;
	alc->table = make_table(alc);
	if (!alc->table)
		return (NULL);
	write_header(alc, alc->zn, 1, zn_size);
	return (alc);
}

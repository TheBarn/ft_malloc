/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ini.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 15:58:31 by barnout           #+#    #+#             */
/*   Updated: 2018/09/24 17:55:14 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

extern	t_dib	*g_dib;

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

/*
	ft_putstr("\nWRITE ");
	ft_putchar(' ');
	ft_putptr((void *)alc);
	ft_putchar(' ');
	ft_putptr(bl);
	ft_putchar(' ');
	ft_putnbr((int)fr);
	ft_putchar(' ');
	ft_putnbr(size);
*/
	((t_head *)bl)->sym = SYM;
	((t_head *)bl)->free = fr;
	((t_head *)bl)->size = size;
	ad = get_ad(alc, bl);
	bl_size = get_block_size(alc, bl);
	ind = write_header_in_table(alc, ad, bl_size);
	return (ind);
}

void	*ft_mmap(size_t size)
{
	void	*ptr;
	int		nb_pg;

	nb_pg = (size + (size_t)getpagesize() - 1) / (size_t)getpagesize();
	if (g_dib)
		g_dib->nb_pg += nb_pg;
	ft_putstr("MMAP size ");
	ft_put_size_t(size);
	ft_putstr(" page ");
	ft_put_size_t(nb_pg);
	ft_putchar('\n');
	ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, \
			   MAP_ANON | MAP_PRIVATE, -1, 0);
	if (!ptr)
		throw_error("Error: mmap allocation: no space found\n");
	return (ptr);
}

int		*make_table(t_alloc *alc)
{
	size_t	nb;
	size_t	size;
	int		*table;

	nb = sum_power_of_two(0, alc->max - alc->min);
	size = nb * (int)sizeof(int);
	table = ft_mmap(size);
//TEST if zero filled
//	memset(table, 0, size);
	return (table);
}

//TODO norme on libft
t_alloc	*make_alloc(int min, int max)
{
	t_alloc	*alc;
	void	*zn;

	//put in dib !!
	alc = ft_mmap(sizeof(t_alloc));
	alc->min = min;
	alc->max = max;
	alc->size = getpagesize() * (power_of_two(max - power_of_two_ind(getpagesize())) + 1);
	alc->left = alc->size - HEAD_SIZE;
	zn = ft_mmap(alc->size);
	if (!zn)
		return (NULL);
	alc->zn = zn;
	alc->table = make_table(alc);
	if (!alc->table)
		return (NULL);
	write_header(alc, alc->zn, 1, alc->size - HEAD_SIZE);
	return (alc);
}

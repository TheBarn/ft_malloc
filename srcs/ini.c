/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ini.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 15:58:31 by barnout           #+#    #+#             */
/*   Updated: 2018/09/19 12:36:03 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int		find_seq_start(t_alloc *alc, int ind)
{
	int		s;

	s = sum_power_of_two(alc->max - ind + 1, alc->max - alc->min);
	return (s);
}

int		write_header_in_table(t_alloc *alc, void *bl, int bl_size)
{
	int		s;
	int		i;
	int		len;
	int		ind;

	ft_putchar('r');
	ind = power_of_two_ind(bl_size);
	ft_putchar('s');
	s = find_seq_start(alc, ind);
	ft_putchar('t');
	i = 0;
	len = power_of_two(alc->max - ind);
	ft_putchar('u');
	while (i < len && (alc->table)[s + i] != NULL)
		i++;
	ft_putchar('v');
	alc->table[s + i] = bl;
	ft_putchar('w');
	return (s + i);
}

int		write_header(t_alloc *alc, void *bl, char fr, int bl_size)
{
	int		ind;

	ft_putstr("\nWRITE: ");
	ft_putptr((void *)alc);
	ft_putchar(' ');
	ft_putptr(bl);
	ft_putchar(' ');
	ft_putnbr((int)fr);
	ft_putchar(' ');
	ft_putnbr(bl_size);
	ft_putchar('\n');
	ft_putchar('m');
	((t_head *)bl)->sym = SYM;
	ft_putchar('n');
	((t_head *)bl)->free = fr;
	ft_putchar('o');
	((t_head *)bl)->size = bl_size;
	ft_putchar('p');
	ind = write_header_in_table(alc, bl, bl_size);
	ft_putchar('q');
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

void	*make_table(t_alloc *alc)
{
	int		ind;
	size_t	nb;
	size_t	size;
	void	**table;

	ind = alc->max;
	nb = sum_power_of_two(alc->min, ind);
	size = nb * (int)sizeof(void *);
	table = mmap(NULL, size, PROT_READ | PROT_WRITE, \
										MAP_ANON | MAP_PRIVATE, -1, 0);
	if (!table)
	{
		throw_error("Error: mmap allocation: no space found\n");
		return (NULL);
	}
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
	ft_putchar('\n');
	ft_putnbr(max);
	//TODO multiple of getpagesize()
	zn_size = power_of_two(max);
	ft_putstr("\nZN_SIZE: ");
	ft_putnbr(zn_size);
	ft_putchar('\n');
	alc->left = zn_size - HEAD_SIZE;
	zn = get_new_zone(zn_size);
	if (!zn)
		return (NULL);
	alc->zn = zn;
	alc->table = make_table(alc);
	if (!alc->table)
		return (NULL);
	write_header(alc, zn, 1, zn_size);
	return (alc);
}

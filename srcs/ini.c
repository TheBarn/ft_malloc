/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ini.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 15:58:31 by barnout           #+#    #+#             */
/*   Updated: 2018/09/26 17:24:32 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

extern	t_dib	*g_dib;

void	write_header(void *bl, char fr, char side, int mem_size)
{
	((t_head *)bl)->sym = SYM;
	((t_head *)bl)->free = fr;
	((t_head *)bl)->offset = 0;
	((t_head *)bl)->side = side;
	((t_head *)bl)->size = mem_size;
/*	ft_putstr("\nWRITE ");
	ft_putptr(bl);
	ft_putchar(' ');
	ft_putnbr((int)fr);
	ft_putchar(' ');
	ft_putnbr(mem_size);
	ft_putchar('\n');
*/
}

void	*ft_mmap(size_t size)
{
	void	*ptr;
	int		nb_pg;

	nb_pg = (size + (size_t)getpagesize() - 1) / (size_t)getpagesize();
	if (g_dib)
		g_dib->nb_pg += nb_pg;
/*	ft_putstr("MMAP size ");
	ft_put_size_t(size);
	ft_putstr(" page ");
	ft_put_size_t(nb_pg);
	ft_putchar('\n');
*/
	ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, \
			   MAP_ANON | MAP_PRIVATE, -1, 0);
	if (!ptr)
		throw_error("Error: mmap allocation: no space found\n");
	return (ptr);
}

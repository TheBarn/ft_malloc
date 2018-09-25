/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ini.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 15:58:31 by barnout           #+#    #+#             */
/*   Updated: 2018/09/25 15:02:47 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

extern	t_dib	*g_dib;

void	write_header(void *bl, char fr, int mem_size)
{
	((t_head *)bl)->sym = SYM;
	((t_head *)bl)->free = fr;
	((t_head *)bl)->offset = 0;
	((t_head *)bl)->size = mem_size;
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

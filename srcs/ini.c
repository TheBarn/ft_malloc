/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ini.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 15:58:31 by barnout           #+#    #+#             */
/*   Updated: 2018/09/27 15:10:18 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	write_header(void *bl, char fr, char side, int mem_size)
{
	((t_head *)bl)->sym = SYM;
	((t_head *)bl)->free = fr;
	((t_head *)bl)->offset = 0;
	((t_head *)bl)->side = side;
	((t_head *)bl)->size = mem_size;
}

void	*ft_mmap(size_t size)
{
	void	*ptr;
	int		nb_pg;

	nb_pg = (size + (size_t)getpagesize() - 1) / (size_t)getpagesize();
	if (g_dib)
		g_dib->nb_pg += nb_pg;
	ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, \
								MAP_ANON | MAP_PRIVATE, -1, 0);
	if (!ptr)
		write(2, "Error: mmap allocation: no space found\n", \
				ft_strlen("Error: mmap allocation: no space found\n"));
	return (ptr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 10:28:21 by barnout           #+#    #+#             */
/*   Updated: 2018/09/24 11:44:09 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

extern	t_dib	*g_dib;

void		show_dib_state(void)
{
	int		i;

	ft_putstr("\nDIB STATE:\n");
	ft_putstr("TINY ALLOCATIONS:");
	i = 0;
	while (i < g_dib->tiny_nb)
	{
		ft_putchar(' ');
		ft_putptr((void*)g_dib->tiny_alc[i++]);
	}
	ft_putchar('\n');
	ft_putstr("SMALL ALLOCATIONS:");
	i = 0;
	while (i < g_dib->small_nb)
	{
		ft_putchar(' ');
		ft_putptr((void *)g_dib->small_alc[i++]);
	}
	ft_putchar('\n');
	ft_putstr("BIG ALLOCATIONS:");
	i = 0;
	while (i < g_dib->big_nb)
	{
		ft_putchar(' ');
		ft_putptr(g_dib->big_alc[i++]);
	}
	ft_putchar('\n');
	ft_putstr("DIB SIZE: ");
	ft_putnbr(g_dib->size);
	ft_putstr("\n\n");
}

int			get_allocated_mem_size(t_alloc *alc)
{
	int		i;
	int		len;
	int		bl_size;
	void	*bl;
	t_head	*h;
	int		alc_mem_size;

	i = 0;
	len = power_of_two(alc->max);
	bl = alc->zn;
	alc_mem_size = 0;
	while (i < len)
	{
		h = (t_head *)bl;
		if (h->sym != SYM)
			throw_error("not a memory block\n");
		bl_size = get_block_size(bl);
		bl = bl + bl_size;
		i += bl_size;
		if (h->free == 0)
			alc_mem_size += bl_size;
	}
	return (alc_mem_size);
}

void		show_zone_state(t_alloc *alc)
{
	int		alc_mem_size;

	ft_putstr("\nZONE: ");
	ft_putptr((void*)alc);
	ft_putchar('\n');
	ft_putstr("MIN ");
	ft_putnbr(power_of_two(alc->min));
	ft_putstr(" MAX ");
	ft_putnbr(power_of_two(alc->max));
	ft_putstr(" LEFT ");
	ft_putnbr(alc->left);
	ft_putchar('\n');
	alc_mem_size = get_allocated_mem_size(alc);
	ft_putstr("ALLOCATED MEMORY: ");
	ft_putnbr(alc_mem_size);
	ft_putstr("\nFREE MEMORY: ");
	ft_putnbr(power_of_two(alc->max) - alc_mem_size);
	ft_putchar('\n');
}

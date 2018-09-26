/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/26 15:59:30 by barnout           #+#    #+#             */
/*   Updated: 2018/09/26 16:50:49 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int		get_len(t_alloc *alc, void *bl)
{
	int		bl_size;
	int		len;
	int		mock_size;

	bl_size = get_block_size(alc, bl);
	len = 4096;
	mock_size = alc->size;
	while (mock_size != bl_size)
	{
		mock_size /= 2;
		len /=2;
		if (len == 1)
			return (len);
	}
	return (len);
}

void	print_visu(t_alloc *alc)
{
	void	*bl;
	t_head	*h;
	int		bl_size;
	int		i;
	int		color;
	int		j;
	int		len;

	ft_putchar('\n');
	bl = alc->zn;
	i = 0;
	while (i < alc->size)
	{
		ft_putptr(bl);
		ft_putchar(':');
		h = (t_head *)bl;
		ft_putnbr(h->size);
		if (h->sym != SYM)
			throw_error("visu error\n");
		if (h->free == 1)
			color = GREEN;
		else
			color = RED;
		ft_putstr("\033[");
		ft_putnbr(color);
		ft_putchar('m');
		j = 0;
		len = get_len(alc, bl);
		while (j++ < len)
			ft_putchar(' ');
		ft_putstr("\033[0m");
		bl_size = get_block_size(alc, bl);
		i += bl_size;
		bl += bl_size;
	}
	ft_putchar('\n');
}

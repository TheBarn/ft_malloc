/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 15:06:21 by barnout           #+#    #+#             */
/*   Updated: 2018/09/27 15:16:49 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int			ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

static void	ft_putptr_req(size_t ad)
{
	char	d;

	d = ad % 16;
	if (ad > 0)
		ft_putptr_req(ad / 16);
	if (d < 10)
		ft_putchar('0' + d);
	else
		ft_putchar('a' + d - 10);
}

void		ft_putptr(void *ptr)
{
	size_t	ad;

	ad = (size_t)ptr;
	ft_putstr("0x");
	ft_putptr_req(ad);
}

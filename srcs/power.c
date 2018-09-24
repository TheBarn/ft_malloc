/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   power.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 16:34:10 by barnout           #+#    #+#             */
/*   Updated: 2018/09/24 16:50:42 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int		count_digit(int n)
{
	int				count;
	unsigned int	nb;

	count = 1;
	if (n < 0)
		nb = (unsigned int)-n;
	else
		nb = (unsigned int)n;
	while (nb > 9)
	{
		nb = (nb - (nb % 10)) / 10;
		count++;
	}
	return (count);
}

int		sup_power_of_two(int nb)
{
	int		i;
	int		p;

	i = 0;
	p = 1;
	while (p < nb)
	{
		p = power_of_two(i);
		i++;
	}
	return (p);
}

size_t	power_of_two(int pow)
{
	int		i;
	size_t	num;

	i = 0;
	num = 1;
	if (pow < 0 || pow > 30)
		return (0);
	while (i < pow)
	{
		num = 2 * num;
		i++;
	}
	return (num);
}

int		power_of_two_ind(int num)
{
	int		max;
	int		i;

	i = 30;
	max = power_of_two(i);
	while (max >= num)
		max = power_of_two(i--);
	return (i + 1);
}

size_t	sum_power_of_two(int start, int end)
{
	size_t	nb;

	nb = 0;
	while (start <= end)
	{
		nb += power_of_two(start);
		start++;
	}
	return (nb);
}

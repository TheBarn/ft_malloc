/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   power.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 16:34:10 by barnout           #+#    #+#             */
/*   Updated: 2018/09/18 15:21:18 by barnout          ###   ########.fr       */
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
	int		i;

	if (num > INT_MAX)
		return (0);
	i = 0;
	while (num > 1 && num % 2 == 0)
	{
		num = num / 2;
		i++;
	}
	return (i);
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

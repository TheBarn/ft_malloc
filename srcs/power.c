/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   power.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 16:34:10 by barnout           #+#    #+#             */
/*   Updated: 2018/09/13 09:36:53 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int		power_of_two(int pow)
{
	int		i;
	int		num;

	i = 0;
	num = 1;
	if (pow < 0 || pow > 30)
		return 0;
	while (i < pow)
	{
		num = 2 * num;
		i++;
	}
	return(num);
}

int		power_of_two_ind(int num)
{
	int		i;

	if (num > INT_MAX)
		return(0);
	i = 0;
	while (num > 1 && num % 2 == 0)
	{
		num = num / 2;
		i++;
	}
	return i;
}

int		sum_power_of_two(int start, int end)
{
	int		nb;

	nb = 0;
	while (start <= end)
	{
		nb += power_of_two(start);
		start++;
	}
	return nb;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 22:23:43 by barnout           #+#    #+#             */
/*   Updated: 2016/12/02 20:15:28 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int		ft_atoi(const char *str)
{
	int		n;
	int		minus;

	n = 0;
	minus = 1;
	while ((*str >= 0 && *str <= 32) || *str == 127)
		str++;
	if (*str == '-')
	{
		minus = -1;
		str++;
	}
	if (*str == '+' && minus == 1)
		str++;
	while (*str >= '0' && *str <= '9')
	{
		n = 10 * n - (*str - '0');
		str++;
	}
	return (minus * -n);
}

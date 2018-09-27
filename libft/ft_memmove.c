/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 22:01:52 by barnout           #+#    #+#             */
/*   Updated: 2016/11/27 17:33:21 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t				i;
	unsigned char		*s1;
	unsigned const char	*s2;

	i = 0;
	s1 = (unsigned char *)dst;
	s2 = (unsigned const char *)src;
	if (src >= dst)
	{
		while (i < len)
		{
			s1[i] = s2[i];
			i++;
		}
	}
	else
	{
		while (i < len)
		{
			s1[len - (i + 1)] = s2[len - (i + 1)];
			i++;
		}
	}
	return (dst);
}

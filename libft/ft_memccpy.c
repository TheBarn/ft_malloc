/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 21:15:37 by barnout           #+#    #+#             */
/*   Updated: 2016/12/02 20:00:13 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*big;
	unsigned char	*little;
	unsigned char	ch;

	ch = (unsigned char)c;
	big = (unsigned char *)dst;
	little = (unsigned char *)src;
	while (n > 0 && *little != ch)
	{
		*big++ = *little++;
		n--;
	}
	if (n > 0 && *little == ch)
	{
		*big = *little;
		big++;
		dst = big;
		return (dst);
	}
	return (NULL);
}

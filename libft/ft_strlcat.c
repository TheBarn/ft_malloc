/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 20:56:08 by barnout           #+#    #+#             */
/*   Updated: 2016/11/27 17:17:26 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		i;
	size_t		len1;
	size_t		len2;

	i = 0;
	len2 = ft_strlen(src);
	while (dst[i] != '\0' && i < size)
		i++;
	if (i == size)
		return (size + len2);
	len1 = ft_strlen(dst);
	while (i < len1 + len2 && i < size - 1)
	{
		dst[i] = src[i - len1];
		i++;
	}
	dst[i] = '\0';
	return (len1 + len2);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 21:39:22 by barnout           #+#    #+#             */
/*   Updated: 2016/11/27 17:19:16 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t		i;
	size_t		len1;
	size_t		len2;

	i = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (s2 == 0 || n == 0)
		return (s1);
	while (i < n && i < len2)
	{
		s1[i + len1] = s2[i];
		i++;
	}
	s1[i + len1] = '\0';
	return (s1);
}

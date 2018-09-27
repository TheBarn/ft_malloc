/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 21:32:11 by barnout           #+#    #+#             */
/*   Updated: 2016/11/27 17:35:41 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	*str;

	i = 0;
	c = (char)c;
	str = (char *)s;
	if (c == '\0')
	{
		while (str[i] != '\0')
			i++;
		return (&str[i]);
		i = 0;
	}
	while (str[i] != '\0' && str[i] != c)
		i++;
	if (str[i] == '\0')
		return (NULL);
	return (&str[i]);
}

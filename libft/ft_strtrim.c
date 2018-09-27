/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 22:43:04 by barnout           #+#    #+#             */
/*   Updated: 2016/11/27 18:41:01 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int		isblankspace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	return (0);
}

static size_t	ft_start(char const *s)
{
	size_t		i;

	i = 0;
	while (isblankspace(s[i]) == 1)
		i++;
	return (i);
}

static size_t	ft_end(char const *s, size_t len)
{
	size_t		i;

	i = len - 1;
	while (isblankspace(s[i]) == 1)
		i--;
	return (i);
}

char			*ft_strtrim(char const *s)
{
	size_t		len;
	size_t		start;
	size_t		end;
	char		*dst;

	len = ft_strlen(s);
	if (isblankspace(s[0]) + isblankspace(s[len - 1]) == 0)
	{
		dst = (char *)s;
		return (dst);
	}
	start = ft_start(s);
	end = ft_end(s, len);
	if (start == len)
	{
		end = 1;
		start = 2;
	}
	dst = ft_strsub(s, start, end - start + 1);
	return (dst);
}

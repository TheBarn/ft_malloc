/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 22:06:37 by barnout           #+#    #+#             */
/*   Updated: 2016/11/27 17:17:05 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmap(char const *s, char (*f)(char))
{
	size_t	i;
	char	*str;
	size_t	len;

	i = 0;
	len = ft_strlen(s);
	str = ft_strnew(len);
	if (str == NULL)
		return (NULL);
	while (s[i] != 0)
	{
		str[i] = f(s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}

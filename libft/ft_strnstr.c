/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 13:45:13 by barnout           #+#    #+#             */
/*   Updated: 2016/11/27 17:39:21 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	k;
	char	*str;

	i = 0;
	k = 0;
	str = (char *)big;
	if (ft_strlen(little) == 0)
		return (str);
	if (ft_strlen(big) < ft_strlen(little))
		return (NULL);
	while (k <= ft_strlen(big) - ft_strlen(little) && k < len)
	{
		while (little[i] == big[i + k] && k + i < len)
		{
			i++;
			if (i == ft_strlen(little))
				return (&str[k]);
		}
		k++;
		i = 0;
	}
	return (NULL);
}

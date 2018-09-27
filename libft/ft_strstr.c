/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 21:54:52 by barnout           #+#    #+#             */
/*   Updated: 2016/11/27 17:25:20 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
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
	while (k <= ft_strlen(big) - ft_strlen(little))
	{
		while (little[i] == big[i + k])
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

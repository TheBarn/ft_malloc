/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 14:47:29 by barnout           #+#    #+#             */
/*   Updated: 2016/11/27 17:10:58 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void		ft_putendl_fd(char const *s, int fd)
{
	unsigned int	i;
	char			endl;

	i = 0;
	while (s[i] != '\0')
		write(fd, &s[i++], 1);
	endl = '\n';
	write(fd, &endl, 1);
}

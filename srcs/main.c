/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 16:19:05 by barnout           #+#    #+#             */
/*   Updated: 2018/09/14 16:51:55 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

//TODO use global variable for dib
//SEE if buddy addresses are efficient or not
//IMPROVE by reallocating freed memory on big allocations
//TEST small zones
//CAN I store tables on dib page ?
int		main()
{
	t_dib		*dib;
	int			i;
	void		*ptr1;
	void		*ptr2;
	void		*ptr3;

	dib = ini_dib();
	i = 0;
	ptr1 = ft_malloc(dib, 8);
	ptr2 = ft_malloc(dib, 60);
	ptr3 = ft_malloc(dib, 500);
	ft_free(dib, ptr2);
	ft_free(dib, ptr3);
	ft_realloc(dib, ptr1, 500);
	while (i < 8)
	{
		ft_malloc(dib, 500);
		i++;
	}
	ft_free(dib, ptr1);
	return(0);
}

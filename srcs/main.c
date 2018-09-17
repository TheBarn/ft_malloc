/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 16:19:05 by barnout           #+#    #+#             */
/*   Updated: 2018/09/17 12:14:33 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_dib	*g_dib = NULL;

//TODO use global variable for g_dib
//SEE if buddy addresses are efficient or not
//IMPROVE by reallocating freed memory on big allocations
//TEST small zones
//CAN I store tables on g_dib page ?
//PRINT by increasing adresses
int		main()
{
	int			i;
	void		*ptr1;
	void		*ptr2;
	void		*ptr3;

	ini_dib();
	i = 0;
	ptr1 = ft_malloc(8);
	ptr2 = ft_malloc(60);
	ptr3 = ft_malloc(500);
	ft_free(ptr2);
	ft_free(ptr3);
	ft_realloc(ptr1, 500);
	while (i < 8)
	{
		ft_malloc(500);
		i++;
	}
	ft_free(ptr1);
	return(0);
}

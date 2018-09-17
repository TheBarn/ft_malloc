/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 16:19:05 by barnout           #+#    #+#             */
/*   Updated: 2018/09/17 14:48:16 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

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
	ptr1 = malloc(8);
	ptr2 = malloc(60);
	ptr3 = malloc(500);
	free(ptr2);
	free(ptr3);
	realloc(ptr1, 500);
	while (i < 8)
	{
		malloc(500);
		i++;
	}
	free(ptr1);
	return(0);
}

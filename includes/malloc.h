/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 09:07:48 by barnout           #+#    #+#             */
/*   Updated: 2018/09/11 16:46:38 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include "libft.h"
# include <stdio.h>
# include <unistd.h>
# include <sys/mman.h>
# include <limits.h>

typedef struct		s_head
{
	char			sym;
	char			free;
	int				size;
}					t_head;

int		power_of_two(int pow);
int		power_of_two_ind(int num);
int		sum_power_of_two(int start,int end);
void	print_mem(char *ptr, int size);

#endif

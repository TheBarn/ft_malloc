/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 09:07:48 by barnout           #+#    #+#             */
/*   Updated: 2018/09/12 14:51:28 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# define TINY_MIN 4
# define TINY_MAX 12
# define SMALL_MIN 10
# define SMALL_MAX 20

# include "libft.h"
# include <stdio.h>
# include <unistd.h>
# include <sys/mman.h>
# include <limits.h>

typedef struct		s_alloc
{
	void		*zn;
	void		**table;
	int			min;
	int			max;
}					t_alloc;

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

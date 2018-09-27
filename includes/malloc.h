/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 09:07:48 by barnout           #+#    #+#             */
/*   Updated: 2018/09/27 10:05:42 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# define TINY_LIM 1200
# define TINY_PG_MULTI 33
# define SMALL_LIM 10500
# define SMALL_PG_MULTI 257
# define HEAD_SIZE ((int)sizeof(t_head))
# define BIG_HEAD_SIZE ((int)sizeof(t_big_head))
# define SYM '*'
# define TRASH '.'
# define RED 41
# define GREEN 42
# define SPEED 800000
# define VISU 0

# include "libft.h"
# include <unistd.h>
# include <sys/mman.h>
# include <stdint.h>
# include "typedef.h"

int		get_block_size(t_alloc *alc, void *bl);
//int		sup_power_of_two(int nb);
//size_t	power_of_two(int pow);
//int		power_of_two_ind(int num);
//size_t	sum_power_of_two(int start, int end);
void	write_header(void *bl, char fr, char side, int bl_size);
void	*malloc(size_t size);
//void	print_zone(t_alloc *alc, char *op, void *arg);
void	*realloc(void *src, size_t size);
void	free(void *ptr);
t_alloc	*get_alloc_zone(int size);
void	double_dib_size(void);
void	ini_dib(void);
t_alloc	*find_zone(void *ptr);
//void	print_header(t_alloc *alc);
//int		count_digit(int n);
void	throw_error(char *msg);
void	show_alloc_mem();
void	ft_putptr(void *ptr);
//void	show_dib_state(void);
//void	show_zone_state(t_alloc *alc);
//int		ft_max(int a, int b);
//void	show_table_state(t_alloc *alc);
void	*ft_mmap(size_t size);
void	split_block(t_alloc *alc, void *bl, int mem_size);
char	is_enough_dib_left(int nb);
void	print_visu(t_alloc *alc);

#endif

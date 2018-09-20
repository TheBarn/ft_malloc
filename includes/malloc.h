/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 09:07:48 by barnout           #+#    #+#             */
/*   Updated: 2018/09/20 17:56:50 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# define TINY_MIN 4
# define TINY_MAX 15
# define SMALL_MIN 9
# define SMALL_MAX 30
# define HEAD_SIZE ((int)sizeof(t_head))
# define SYM '*'
# define RED 41
# define GREEN 42
# define SPEED 800000
# define VISU 0

# include "libft.h"
# include <stdio.h>
# include <unistd.h>
# include <sys/mman.h>
# include <limits.h>
# include <stdint.h>
# include <unistd.h>
# include "typedef.h"

int		get_block_size(void *bl);
int		sup_power_of_two(int nb);
size_t	power_of_two(int pow);
int		power_of_two_ind(int num);
size_t	sum_power_of_two(int start, int end);
int		write_header(t_alloc *alc, void *bl, char fr, int bl_size);
t_alloc	*ini_alloc(void);
int		find_seq_start(t_alloc *alc, int ind);
void	*malloc(size_t size);
void	*find_buddy(t_alloc *alc, void *bl);
void	print_zone(t_alloc *alc, char *op, void *arg);
void	*realloc(void *src, size_t size);
void	erase_buddies(t_alloc *alc, void *bl, void *bud);
void	free(void *ptr);
t_alloc	*get_alloc_zone(size_t size);
t_alloc	*make_alloc(int min, int max);
void	double_dib_size(void);
void	ini_dib(void);
t_alloc	*find_zone(void *ptr);
void	print_header(t_alloc *alc);
int		count_digit(int n);
void	throw_error(char *msg);
void	show_alloc_mem();
void	ft_putptr(void *ptr);
int		get_ad(t_alloc *alc, void *bl);
void	*get_block(t_alloc *alc, int ad);

#endif

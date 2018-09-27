/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 09:07:48 by barnout           #+#    #+#             */
/*   Updated: 2018/09/27 15:43:40 by barnout          ###   ########.fr       */
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
# include <pthread.h>

extern t_dib			*g_dib;
extern pthread_mutex_t	g_mutex;

void	*malloc(size_t size);
void	*ft_malloc(size_t size);
void	free(void *ptr);
void	ft_free(void *ptr);
void	*realloc(void *src, size_t size);
void	*ft_realloc(void *src, size_t size);
void	show_alloc_mem(void);
void	ft_show_alloc_mem(void);
int		get_block_size(t_alloc *alc, void *bl);
void	write_header(void *bl, char fr, char side, int bl_size);
t_alloc	*get_alloc_zone(int size);
void	double_dib_size(void);
void	ini_dib(void);
t_alloc	*find_zone(void *ptr);
void	ft_putptr(void *ptr);
void	*ft_mmap(size_t size);
void	split_block(t_alloc *alc, void *bl, int mem_size);
char	is_enough_dib_left(int nb);
void	merge_bud(t_alloc *alc, void *bl);
void	*realloc_big(void *src, size_t size);
int		ft_min(int a, int b);
void	ft_putptr(void *ptr);
t_alloc	*next_alloc(void *pr, size_t *tot);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 09:07:48 by barnout           #+#    #+#             */
/*   Updated: 2018/09/14 15:55:17 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# define TINY_MIN 4
# define TINY_MAX 11
# define TINY_LIM 500
# define SMALL_MIN 10
# define SMALL_MAX 20
# define SMALL_LIM 250000
# define HEAD_SIZE ((int)sizeof(t_head))
# define SYM '*'
# define RED 41
# define GREEN 42
# define SPEED 1000000

# include "libft.h"
# include <stdio.h>
# include <unistd.h>
# include <sys/mman.h>
# include <limits.h>
# include <stdint.h>

typedef struct		s_alloc
{
	void		*zn;
	void		**table;
	int			min;
	int			max;
	int			left;
}					t_alloc;

typedef struct		s_head
{
	char			sym;
	char			free;
	int				size;
}					t_head;

typedef struct		s_dib
{
	t_alloc			**tiny_alc;
	int				tiny_nb;
	t_alloc			**small_alc;
	int				small_nb;
	void			**big_alc;
	int				big_nb;
	int				size;
}					t_dib;

int		power_of_two(int pow);
int		power_of_two_ind(int num);
int		sum_power_of_two(int start,int end);
void	print_mem(char *ptr, int size);
void	dump_table(t_alloc *alc);
int		write_header(t_alloc *alc, void *bl, char fr, int bl_size);
t_alloc     *ini_alloc(void);
int     find_seq_start(t_alloc *alc, int ind);
void	*xor_size(void *ptr, int size);
void	*ft_malloc(t_dib *dib, int size);
void	*find_buddy(void *bl);
void	print_zone(t_alloc *alc, char *op);
void	*ft_realloc(t_dib *dib, void *src, int size);
void	erase_buddies(t_alloc *alc, void *bl, void *bud);
void	ft_free(t_dib *dib, void *ptr);
t_alloc		*get_alloc_zone(t_dib* dib, int size);
t_alloc	*make_alloc(int min, int max);
t_dib	*double_dib_size(t_dib *dib);
t_dib	*ini_dib(void);
t_alloc	*find_zone(t_dib *dib, void *ptr);
void	print_header(t_dib *dib, t_alloc *alc);

#endif

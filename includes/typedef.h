/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 13:24:26 by barnout           #+#    #+#             */
/*   Updated: 2018/09/19 14:22:35 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_H
# define TYPEDEF_H

typedef struct		s_alloc
{
	void		*zn;
	int			*table;
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

#endif
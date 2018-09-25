/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 13:24:26 by barnout           #+#    #+#             */
/*   Updated: 2018/09/25 18:05:51 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_H
# define TYPEDEF_H

typedef struct		s_alloc
{
	int			left;
	int			size;
	void		*zn;
}					t_alloc;

typedef struct		s_head
{
	char			sym;
	char			free;
	char			offset;
	int				size;
}					t_head;

typedef struct		s_dib
{
	t_alloc			*tiny_alc;
	int				tiny_nb;
	t_alloc			*small_alc;
	int				small_nb;
	void			*big_alc;
	int				big_nb;
	int				size;
	int				nb_pg;
}					t_dib;

#endif

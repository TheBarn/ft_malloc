/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 11:40:25 by barnout           #+#    #+#             */
/*   Updated: 2018/09/27 13:41:07 by barnout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_dib				*g_dib = NULL;
pthread_mutex_t		g_mutex = PTHREAD_MUTEX_INITIALIZER;

void		*malloc(size_t size)
{
	void	*ptr;

	pthread_mutex_lock(&g_mutex);
	ini_dib();
	ptr = ft_malloc(size);
	pthread_mutex_unlock(&g_mutex);
	return (ptr);
}

void		*realloc(void *src, size_t size)
{
	void	*ptr;

	pthread_mutex_lock(&g_mutex);
	ini_dib();
	ptr = ft_realloc(src, size);
	pthread_mutex_unlock(&g_mutex);
	return (ptr);
}

void		free(void *ptr)
{
	pthread_mutex_lock(&g_mutex);
	ini_dib();
	ft_free(ptr);
	pthread_mutex_unlock(&g_mutex);
}

void		show_alloc_mem(void)
{
	pthread_mutex_lock(&g_mutex);
	ini_dib();
	ft_show_alloc_mem();
	pthread_mutex_unlock(&g_mutex);
}

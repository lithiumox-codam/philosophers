/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mutex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lithium <lithium@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/03 18:09:25 by lithium       #+#    #+#                 */
/*   Updated: 2023/11/24 14:39:53 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philos.h>

void	free_mutex(void *mutex)
{
	pthread_mutex_destroy(mutex);
	free(mutex);
}

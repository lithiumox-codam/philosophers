/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mutex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lithium <lithium@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/03 18:09:25 by lithium       #+#    #+#                 */
/*   Updated: 2023/11/28 14:22:37 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philos.h>

void	free_mutex(void *mutex)
{
	pthread_mutex_t	*tmp;
	int				destroy_result;

	tmp = (pthread_mutex_t *)mutex;
	destroy_result = pthread_mutex_destroy(tmp);
	if (destroy_result != 0)
	{
		printf("Error: Mutex destroy failed with error code: %d\n",
			destroy_result);
	}
}

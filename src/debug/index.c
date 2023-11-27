/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   index.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/02 22:08:43 by mdekker       #+#    #+#                 */
/*   Updated: 2023/11/27 10:49:19 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <philos.h>

void	print_vec(t_vector *vec, void (*print)(void *))
{
	size_t	i;

	i = 0;
	if (!DEBUG)
		return ;
	while (i < vec->length)
	{
		print(vec_get(vec, i));
		i++;
	}
}

void	print_mutex(void *mutex)
{
	pthread_mutex_t	*mtx;
	int				lock_status;

	mtx = (pthread_mutex_t *)mutex;
	lock_status = pthread_mutex_trylock(mtx);
	if (lock_status == EBUSY)
	{
		printf("\033[1;34m|-- Mutex Address: %p (Status: Locked)\033[0m\n",
			mutex);
	}
	else
	{
		printf("\033[1;34m|-- Mutex Address: %p (Status: Not Locked)\033[0m\n",
			mutex);
		pthread_mutex_unlock(mtx);
	}
}

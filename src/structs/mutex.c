/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mutex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lithium <lithium@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/03 18:09:25 by lithium       #+#    #+#                 */
/*   Updated: 2023/09/03 18:16:18 by lithium       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philos.h>

void	lock_forks(t_philo *philo)
{
	pthread_mutex_lock(vec_get(philo->data->mutexes.forks, philo->id));
	pthread_mutex_lock(vec_get(philo->data->mutexes.forks, (philo->id + 1)
			% philo->data->philo_count));
}

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(vec_get(philo->data->mutexes.forks, philo->id));
	pthread_mutex_unlock(vec_get(philo->data->mutexes.forks, (philo->id + 1)
			% philo->data->philo_count));
}

void	free_mutex(void *mutexes)
{
	size_t i;
	t_mutexes *mutex;

	mutex = (t_mutexes *)mutexes;

	i = 0;
	while (i < mutex->forks->length)
	{
		pthread_mutex_destroy(vec_get(mutex->forks, i));
		i++;
	}
	pthread_mutex_destroy(&mutex->print);
	pthread_mutex_destroy(&mutex->dead);
	pthread_mutex_destroy(&mutex->eat);
	pthread_mutex_destroy(&mutex->eat_count);
	vec_free(mutex->forks);
}
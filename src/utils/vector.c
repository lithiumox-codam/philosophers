/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/03 20:57:15 by mdekker       #+#    #+#                 */
/*   Updated: 2023/11/28 16:40:39 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philos.h>

void	take_forks(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (philo->id % 2 == 0)
	{
		first_fork = (pthread_mutex_t *)vec_get(philo->data->mutexes.forks,
				philo->id);
		second_fork = (pthread_mutex_t *)vec_get(philo->data->mutexes.forks,
				(philo->id + 1) % philo->data->philo_count);
	}
	else
	{
		first_fork = (pthread_mutex_t *)vec_get(philo->data->mutexes.forks,
				(philo->id + 1) % philo->data->philo_count);
		second_fork = (pthread_mutex_t *)vec_get(philo->data->mutexes.forks,
				philo->id);
	}
	pthread_mutex_lock(first_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(second_fork);
	print_status(philo, "has taken a fork");
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	first_fork = (pthread_mutex_t *)vec_get(philo->data->mutexes.forks,
			philo->id);
	pthread_mutex_unlock(first_fork);
	second_fork = (pthread_mutex_t *)vec_get(philo->data->mutexes.forks,
			(philo->id + 1) % philo->data->philo_count);
	pthread_mutex_unlock(second_fork);
}

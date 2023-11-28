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

	// if (philo->id < (philo->id + 1) % philo->data->philo_count)
	// {
	// 	first_fork = (pthread_mutex_t *)vec_get(philo->data->mutexes.forks,
	// 			philo->id);
	// 	second_fork = (pthread_mutex_t *)vec_get(philo->data->mutexes.forks,
	// 			(philo->id + 1) % philo->data->philo_count);
	// }
	// else
	// {
	// 	first_fork = (pthread_mutex_t *)vec_get(philo->data->mutexes.forks,
	// 			(philo->id + 1) % philo->data->philo_count);
	// 	second_fork = (pthread_mutex_t *)vec_get(philo->data->mutexes.forks,
	// 			philo->id);
	// }
	first_fork = (pthread_mutex_t *)vec_get(philo->data->mutexes.forks,
			philo->id);
	second_fork = (pthread_mutex_t *)vec_get(philo->data->mutexes.forks,
			(philo->id + 1) % philo->data->philo_count);
	pthread_mutex_lock(philo->data->mutexes.print);
	pthread_mutex_lock(first_fork);
	printf("%zu %zu has taken a fork\n", start_diff(philo), philo->id + 1);
	pthread_mutex_unlock(philo->data->mutexes.print);
	pthread_mutex_lock(second_fork);
	pthread_mutex_lock(philo->data->mutexes.print);
	printf("%zu %zu has taken a fork\n", start_diff(philo), philo->id + 1);
	pthread_mutex_unlock(philo->data->mutexes.print);
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

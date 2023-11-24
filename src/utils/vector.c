/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/03 20:57:15 by mdekker       #+#    #+#                 */
/*   Updated: 2023/11/24 17:15:42 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philos.h>

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock((pthread_mutex_t *)vec_get(philo->data->mutexes.forks,
			philo->id));
	printf("%zu %zu has taken a fork\n", start_diff(philo), philo->id + 1);
	pthread_mutex_lock((pthread_mutex_t *)vec_get(philo->data->mutexes.forks,
			(philo->id + 1) % philo->data->philo_count));
	printf("%zu %zu has taken a fork\n", start_diff(philo), philo->id + 1);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock((pthread_mutex_t *)vec_get(philo->data->mutexes.forks,
			philo->id));
	pthread_mutex_unlock((pthread_mutex_t *)vec_get(philo->data->mutexes.forks,
			(philo->id + 1) % philo->data->philo_count));
}

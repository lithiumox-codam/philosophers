/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/03 20:57:15 by mdekker       #+#    #+#                 */
/*   Updated: 2023/11/27 10:51:21 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philos.h>

void	take_forks(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	first_fork = (pthread_mutex_t *)vec_get(philo->data->mutexes.forks,
											philo->id);
	pthread_mutex_lock(first_fork);
	printf("%zu %zu has taken a fork\n", start_diff(philo), philo->id + 1);
	second_fork = (pthread_mutex_t *)vec_get(philo->data->mutexes.forks,
												(philo->id + 1)
													% philo->data->philo_count);
	pthread_mutex_lock(second_fork);
	if (!second_fork || !first_fork)
		printf("Fork is NULL\n");
	printf("%zu %zu has taken a fork\n", start_diff(philo), philo->id + 1);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	first_fork = (pthread_mutex_t *)vec_get(philo->data->mutexes.forks,
											philo->id);
	pthread_mutex_unlock(first_fork);
	second_fork = (pthread_mutex_t *)vec_get(philo->data->mutexes.forks,
												(philo->id + 1)
													% philo->data->philo_count);
	if (!second_fork || !first_fork)
		printf("Fork is NULL\n");
	pthread_mutex_unlock(second_fork);
}

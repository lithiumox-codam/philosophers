/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lithium <lithium@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/07 22:42:36 by lithium       #+#    #+#                 */
/*   Updated: 2023/11/24 17:37:48 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philos.h>

size_t	start_diff(t_philo *philo)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return ((current.tv_sec * 1000 + current.tv_usec / 1000)
		- (philo->data->start.tv_sec * 1000 + philo->data->start.tv_usec
			/ 1000));
}

/**
 * @brief Prints the status of the philosopher based on the state enum
 *
 * @param philo The philosopher
 */
bool	print_status(t_philo *philo)
{
	size_t	start_time;

	pthread_mutex_lock(philo->data->mutexes.print);
	start_time = start_diff(philo);
	if (!die_time_check(philo->last_eaten, philo))
		return (false);
	if (philo->state == THINKING)
	{
		printf("%zu %zu is thinking\n", start_time, philo->id + 1);
		philo->state = EATING;
	}
	else if (philo->state == EATING)
		printf("%zu %zu is eating\n", start_time, philo->id + 1);
	else if (philo->state == SLEEPING)
		printf("%zu %zu is sleeping\n", start_time, philo->id + 1);
	pthread_mutex_unlock(philo->data->mutexes.print);
	return (true);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lithium <lithium@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/07 22:42:36 by lithium       #+#    #+#                 */
/*   Updated: 2023/09/08 14:18:41 by mdekker       ########   odam.nl         */
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
void	print_status(t_philo *philo)
{
	size_t		start_time;
	t_vector	*philos;

	philos = philo->data->philos;
	pthread_mutex_lock(philo->data->mutexes.print);
	start_time = start_diff(philo);
	if (philo->state == THINKING)
		printf("%zu %zu is thinking\n", start_time, philo_id(philo, philos));
	else if (philo->state == EATING)
		printf("%zu %zu is eating\n", start_time, philo_id(philo, philos));
	else if (philo->state == SLEEPING)
		printf("%zu %zu is sleeping\n", start_time, philo_id(philo, philos));
	else if (philo->state == DEAD)
		printf("%zu %zu died\n", start_time, philo_id(philo, philos));
	pthread_mutex_unlock(philo->data->mutexes.print);
}

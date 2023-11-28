/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lithium <lithium@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/07 22:42:36 by lithium       #+#    #+#                 */
/*   Updated: 2023/11/28 16:28:27 by mdekker       ########   odam.nl         */
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
bool	print_status(t_philo *philo, char *msg)
{
	pthread_mutex_lock(philo->data->mutexes.print);
	if (!philo->data->dead)
		printf("%zu %zu %s\n", start_diff(philo), philo->id + 1, msg);
	pthread_mutex_unlock(philo->data->mutexes.print);
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/02 16:20:23 by mdekker       #+#    #+#                 */
/*   Updated: 2023/12/02 20:41:39 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philos.h>

/**
 * @brief Get the time in milliseconds
 *
 * @return size_t The time in milliseconds
 */
size_t	get_time(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

/**
 * @brief A function that returns if the time started and the current time
 * is bigger than the time to die and the philosopher is not eating
 *
 * @param start
 * @param philo
 * @return size_t
 */
bool	die_time_check(t_philo *philo)
{
	bool	result;

	pthread_mutex_lock(&philo->lock);
	result = (get_time() - philo->last_eaten) < philo->data->time_to_die;
	pthread_mutex_unlock(&philo->lock);
	return (result);
}

/**
 * @brief A function that returns the difference between the start time and
 * the current time
 * @param stamp The start time
 * @return size_t
 */
size_t	curr_time_diff(size_t stamp)
{
	return (get_time() - stamp);
}

/**
 * @brief Function to wait for a semi certain amount of time
 * @param time The time to wait in milliseconds
 */
void	wait_for(size_t time)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(250);
}

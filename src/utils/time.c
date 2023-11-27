/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/02 16:20:23 by mdekker       #+#    #+#                 */
/*   Updated: 2023/11/27 16:58:56 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philos.h>

/**
 * @brief Gets the current time in milliseconds
 *
 * @return size_t The current time in milliseconds
 */
struct timeval	current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time);
}

/**
 * @brief A function that returns if the time started and the current time
 * is bigger than the time to die and the philosopher is not eating
 *
 * @param start
 * @param philo
 * @return size_t
 */
bool	die_time_check(struct timeval start, t_philo *philo)
{
	size_t	time_diff;

	pthread_mutex_lock(philo->lock);
	time_diff = curr_time_diff(start);
	if (time_diff > philo->data->time_to_die)
	{
		pthread_mutex_unlock(philo->lock);
		drop_forks(philo);
		return (false);
	}
	pthread_mutex_unlock(philo->lock);
	return (true);
}

size_t	curr_time_diff(struct timeval start)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000 + now.tv_usec / 1000) - (start.tv_sec * 1000
			+ start.tv_usec / 1000));
}

/**
 * @brief Function to wait for a semi certain amount of time
 * @param time The time to wait in milliseconds
 * @note This function is not very accurate (on purpose)
 */
void	wait_for(t_philo *philo, size_t time)
{
	struct timeval	start;

	start = current_time();
	while (curr_time_diff(start) < time)
	{
		if (!die_time_check(philo->last_eaten, philo))
			return ;
		usleep(200);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/02 16:20:23 by mdekker       #+#    #+#                 */
/*   Updated: 2023/11/29 17:41:02 by mdekker       ########   odam.nl         */
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
	pthread_mutex_lock(philo->data->mutexes.eat);
	if (curr_time_diff(start) >= philo->data->time_to_die)
		return (pthread_mutex_unlock(philo->data->mutexes.eat), false);
	pthread_mutex_unlock(philo->data->mutexes.eat);
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
 */
void	wait_for(t_philo *philo, size_t time)
{
	struct timeval	start;

	(void)philo;
	start = current_time();
	while (curr_time_diff(start) < time)
	{
		if (check_death(philo))
			return ;
		usleep(time / 10);
	}
}

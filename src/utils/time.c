/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/02 16:20:23 by mdekker       #+#    #+#                 */
/*   Updated: 2023/09/08 14:32:24 by mdekker       ########   odam.nl         */
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

size_t	get_time_diff(struct timeval start)
{
	struct timeval	now;
	size_t			diff;

	gettimeofday(&now, NULL);
	diff = (now.tv_sec - start.tv_sec) * 1000;
	diff += (now.tv_usec - start.tv_usec) / 1000;
	return (diff);
}

/**
 * @brief Function to wait for a semi certain amount of time
 * @param time The time to wait in milliseconds
 * @note This function is not very accurate (on purpose)
 */
void	wait_for(size_t time)
{
	struct timeval	start;

	start = current_time();
	while (get_time_diff(start) < time)
		usleep(200);
}

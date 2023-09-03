/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/02 16:20:23 by mdekker       #+#    #+#                 */
/*   Updated: 2023/09/02 16:20:41 by mdekker       ########   odam.nl         */
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
 * @brief Gets the time difference between two times in milliseconds
 *
 * @param start The start time
 * @param end The end time
 * @return size_t The time difference in milliseconds
 */
size_t	time_diff(struct timeval start, struct timeval end)
{
	return (end.tv_usec - start.tv_usec + (end.tv_sec - start.tv_sec) * 1000);
}

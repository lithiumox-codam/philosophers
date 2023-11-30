/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lithium <lithium@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/07 22:42:36 by lithium       #+#    #+#                 */
/*   Updated: 2023/11/30 20:21:57 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philos.h>

/**
 * @brief Prints the status of the philosopher based on the state enum
 *
 * @param philo The philosopher
 */
bool	print_status(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->print);
	if (check_death(philo))
		return (pthread_mutex_unlock(&philo->data->print), false);
	printf("%zu %zu %s\n", curr_time_diff(philo->data->start_time), philo->id
		+ 1, msg);
	pthread_mutex_unlock(&philo->data->print);
	return (true);
}

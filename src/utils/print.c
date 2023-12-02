/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lithium <lithium@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/07 22:42:36 by lithium       #+#    #+#                 */
/*   Updated: 2023/12/03 00:25:33 by lithium       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philos.h>

/**
 * @brief Prints the status of the philosopher if it is not dead
 *
 * @note The function checks if a philosopher is dead before printing
 * because no other thread should be able to print if a philosopher is dead
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/02 16:50:29 by mdekker       #+#    #+#                 */
/*   Updated: 2023/09/02 22:50:36 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philos.h>

t_philo	create_philo(size_t id)
{
	t_philo	philo;

	philo.id = id;
	philo.state = THINKING;
	philo.eat_count = 0;
	philo.last_eaten = current_time();
	return (philo);
}

void	free_philo(void *philo)
{
	free(philo);
}

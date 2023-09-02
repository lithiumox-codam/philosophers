/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/02 16:50:29 by mdekker       #+#    #+#                 */
/*   Updated: 2023/09/02 16:55:44 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philos.h>

t_philo	create_philo(size_t id, t_data *data)
{
	t_philo	philo;

	philo.id = id;
	philo.state = THINKING;
	philo.eat_count = 0;
	philo.last_eat = get_time();
	philo.left_fork = id;
	philo.right_fork = (id + 1) % data->philo_count;
	return (philo);
}

t_philo	free_philo(t_philo philo)
{
	free(philo);
	return (NULL);
}

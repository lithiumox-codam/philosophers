/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleanup.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/27 12:30:07 by mdekker       #+#    #+#                 */
/*   Updated: 2023/12/02 20:58:47 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philos.h>

static void	clean_mutexes(t_data *data)
{
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->dead);
	pthread_mutex_destroy(&data->eat);
	pthread_mutex_destroy(&data->start);
}

void	cleanup(t_data *data)
{
	size_t	i;

	// (void)data;
	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_destroy(&data->philos[i].lock);
		i++;
	}
	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
	free(data->philos);
	clean_mutexes(data);
}

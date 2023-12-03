/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleanup.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/27 12:30:07 by mdekker       #+#    #+#                 */
/*   Updated: 2023/12/03 14:19:37 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philos.h>

void	clean_created_philo(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->philo_count)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}

void	clean_mutexes(t_data *data, bool forks)
{
	size_t	i;

	i = 0;
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->dead);
	pthread_mutex_destroy(&data->eat);
	pthread_mutex_destroy(&data->start);
	if (forks)
	{
		while (i < data->philo_count)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
		data->forks = NULL;
	}
}

void	cleanup(t_data *data)
{
	size_t	i;

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
	clean_mutexes(data, false);
}

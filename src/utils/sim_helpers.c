/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sim_helpers.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lithium <lithium@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/02 23:42:20 by lithium       #+#    #+#                 */
/*   Updated: 2023/12/03 00:00:54 by lithium       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philos.h>

/**
 * @brief Joins all the threads in the philo array so the program can exit
 *
 * @param data The data struct
 */
void	close_all(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->philo_count)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}

/**
 * @brief The singular philo function so the program can not loop infinitely
 *
 * @param data The data struct
 */
void	singular_philo(t_data *data)
{
	size_t	i;

	i = 0;
	pthread_mutex_lock(data->philos[0].left_fork);
	printf("%zu %zu has taken a fork\n", i, data->philos[0].id + 1);
	pthread_mutex_unlock(data->philos[0].left_fork);
	wait_for(data->time_to_die);
	printf("%zu %zu died\n", data->time_to_die, data->philos[0].id + 1);
}

/**
 * @brief A function that kills the created threads created before
 * the error occured
 *
 * @param data The data struct
 * @param i The index of the thread that caused the error
 */
void	kill_created_philos(t_data *data, size_t i)
{
	size_t	j;

	j = 0;
	while (j < i)
	{
		pthread_join(data->philos[j].thread, NULL);
		j++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/03 20:54:54 by mdekker       #+#    #+#                 */
/*   Updated: 2023/12/02 19:33:06 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philos.h>

bool	initialize_mutexes(t_data *data)
{
	size_t	i;

	i = 0;
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->dead, NULL);
	pthread_mutex_init(&data->eat, NULL);
	pthread_mutex_init(&data->start, NULL);
	data->forks = calloc(sizeof(pthread_mutex_t), (data->philo_count));
	if (!data->forks)
		return (print_error("Initialization of forks vector failed!", NULL),
			false);
	while (i < data->philo_count)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	return (true);
}

static bool	init_philos(t_data *data)
{
	t_philo	*philo;

	data->philos = malloc(sizeof(t_philo) * data->philo_count);
	if (!data->philos)
		return (false);
	while (data->philos_created < data->philo_count)
	{
		philo = &data->philos[data->philos_created];
		philo->id = data->philos_created;
		philo->data = data;
		philo->eat_count = 0;
		pthread_mutex_init(&data->philos[data->philos_created].lock, NULL);
		philo->left_fork = &data->forks[data->philos_created];
		philo->right_fork = &data->forks[(data->philos_created + 1)
			% data->philo_count];
		data->philos_created++;
	}
	return (true);
}

/**
 * @brief The function to initialize all used vectors & mutexes
 *
 * @param data The data struct to initialize
 * @return bool Whether the initialization was successful
 */
bool	init(t_data *data, int ac, char **av)
{
	if (!parse_input(data, ac, av))
		return (false);
	if (!initialize_mutexes(data))
		return (false);
	if (!init_philos(data))
		return (false);
	return (true);
}

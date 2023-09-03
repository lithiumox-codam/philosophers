/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/03 20:54:54 by mdekker       #+#    #+#                 */
/*   Updated: 2023/09/03 23:04:36 by lithium       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philos.h>

bool	initialize_mutexes(t_data *data)
{
	t_mutexes		*tmp;
	size_t			i;
	pthread_mutex_t	*fork;

	tmp = &data->mutexes;
	i = 0;
	pthread_mutex_init(&(tmp->print), NULL);
	pthread_mutex_init(&(tmp->dead), NULL);
	pthread_mutex_init(&(tmp->eat), NULL);
	pthread_mutex_init(&(tmp->eat_count), NULL);
	tmp->forks = malloc(sizeof(t_vector));
	if (!tmp->forks || !vec_init(tmp->forks, data->philo_count,
			sizeof(pthread_mutex_t), free_mutex))
		return (false);
	while (i < data->philo_count)
	{
		fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (!fork)
			return (false);
		pthread_mutex_init(fork, NULL);
		vec_push(tmp->forks, fork);
		i++;
	}
	return (true);
}

static bool	init_philos(t_data *data)
{
	t_philo	*philo;
	size_t	i;

	i = 0;
	data->philos = malloc(sizeof(t_vector));
	if (!data->philos || !vec_init(data->philos, data->philo_count,
			sizeof(t_philo), free_philo))
		return (false);
	while (i < data->philo_count)
	{
		philo = (t_philo *)malloc(sizeof(t_philo));
		if (!philo)
			return (print_error("Allocation of philo failed!"), false);
		philo->id = i;
		philo->data = data;
		philo->last_eaten = current_time();
		philo->eat_count = 0;
		philo->state = THINKING;
		philo->data = data;
		if (!vec_push(data->philos, philo))
			return (print_error("Vector push failed with philo!"), false);
		i++;
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

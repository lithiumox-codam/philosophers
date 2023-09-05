/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/03 20:54:54 by mdekker       #+#    #+#                 */
/*   Updated: 2023/09/04 15:59:09 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philos.h>

pthread_mutex_t	*init_mutex(pthread_mutex_t *mutex)
{
	mutex = malloc(sizeof(pthread_mutex_t));
	if (!mutex)
		return (NULL);
	pthread_mutex_init(mutex, NULL);
	return (mutex);
}

bool	initialize_mutexes(t_data *data)
{
	t_mutexes		*tmp;
	size_t			i;
	pthread_mutex_t	*fork;

	tmp = &data->mutexes;
	i = 0;
	tmp->print = init_mutex(tmp->print);
	tmp->dead = init_mutex(tmp->dead);
	tmp->eat = init_mutex(tmp->eat);
	tmp->eat_count = init_mutex(tmp->eat_count);
	tmp->philos_created = init_mutex(tmp->philos_created);
	tmp->forks = malloc(sizeof(t_vector));
	if (!tmp->print || !tmp->dead || !tmp->eat || !tmp->eat_count)
		return (print_error("Initialization of mutexes failed!"), false);
	if (!tmp->forks || !vec_init(tmp->forks, data->philo_count,
			sizeof(pthread_mutex_t), free_mutex))
		return (print_error("Initialization of forks vector failed!"), false);
	while (i < data->philo_count)
	{
		fork = init_mutex(fork);
		if (!fork)
			return (false);
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
		philo->left_fork = (pthread_mutex_t *)vec_get(data->mutexes.forks, i);
		philo->right_fork = (pthread_mutex_t *)vec_get(data->mutexes.forks, (i
					+ 1) % data->philo_count);
		if (!vec_push(data->philos, philo))
			return (print_error("Vector push failed with philo!"), false);
		else
			data->philos_created++;
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

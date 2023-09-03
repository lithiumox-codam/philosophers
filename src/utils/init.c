/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/03 20:54:54 by mdekker       #+#    #+#                 */
/*   Updated: 2023/09/03 18:20:48 by lithium       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philos.h>

bool	initialize_mutexes(t_data *data)
{
	t_mutexes		tmp;
	size_t			i;
	pthread_mutex_t	*fork;

	pthread_mutex_init(&tmp.print, NULL);
	pthread_mutex_init(&tmp.dead, NULL);
	pthread_mutex_init(&tmp.eat, NULL);
	pthread_mutex_init(&tmp.eat_count, NULL);
	vec_init(tmp.forks, data->philo_count, sizeof(pthread_mutex_t), free_mutex);
	if (!tmp.forks)
		return (false);
	i = 0;
	while (i < data->philo_count)
	{
		fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (!fork)
			return (false);
		pthread_mutex_init(fork, NULL);
		vec_push(tmp.forks, fork);
		i++;
	}
	data->mutexes = tmp;
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
	return (true);
}

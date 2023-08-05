/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/03 20:54:54 by mdekker       #+#    #+#                 */
/*   Updated: 2023/08/04 01:05:55 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philos.h>

void	*push_mutexes(t_vector *vec, size_t count)
{
	size_t			i;
	pthread_mutex_t	*mutex;

	i = 0;
	while (i < count)
	{
		mutex = malloc(sizeof(pthread_mutex_t));
		if (!mutex || !vec_push(vec, mutex))
			return (NULL);
		i++;
	}
	return (vec->data);
}

/**
 * @brief The function to initialize all used vectors & mutexes
 *
 * @param data The data struct to initialize
 * @return bool Whether the initialization was successful
 */
bool	init(t_global *data)
{
	if (!vec_init(&data->mutexes.forks, data->philo_count,
			sizeof(pthread_mutex_t), NULL) || !vec_init(&data->mutexes.print, 1,
			sizeof(pthread_mutex_t), NULL) || !vec_init(&data->mutexes.dead, 1,
			sizeof(pthread_mutex_t), NULL) || !vec_init(&data->mutexes.eat, 1,
			sizeof(pthread_mutex_t), NULL)
		|| !vec_init(&data->mutexes.eat_count, 1, sizeof(pthread_mutex_t),
			NULL))
		return (false);
	if (!push_mutexes(&data->mutexes.forks, data->philo_count)
		|| !vec_push(&data->mutexes.print, NULL)
		|| !vec_push(&data->mutexes.dead, NULL) || !vec_push(&data->mutexes.eat,
			NULL) || !vec_push(&data->mutexes.eat_count, NULL))
		return (false);
	return (true);
}

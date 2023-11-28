/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleanup.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/27 12:30:07 by mdekker       #+#    #+#                 */
/*   Updated: 2023/11/28 14:36:39 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philos.h>

static void	clean_mutexes(t_mutexes *mutexes)
{
	pthread_mutex_destroy(mutexes->print);
	pthread_mutex_destroy(mutexes->dead);
	pthread_mutex_destroy(mutexes->eat);
	free(mutexes->print);
	free(mutexes->dead);
	free(mutexes->eat);
}

void	cleanup(t_data *data)
{
	// (void)data;
	pthread_mutex_lock(data->mutexes.dead);
	data->dead = true;
	pthread_mutex_unlock(data->mutexes.dead);
	vec_free(data->philos);
	vec_free(data->mutexes.forks);
	free(data->mutexes.forks->data);
	clean_mutexes(&data->mutexes);
	exit(0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleanup.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/27 12:30:07 by mdekker       #+#    #+#                 */
/*   Updated: 2023/11/27 16:47:34 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philos.h>

static void	clean_mutexes(t_mutexes *mutexes)
{
	printf("cleaning mutex struct!\n");
	pthread_mutex_destroy(mutexes->print);
	pthread_mutex_destroy(mutexes->dead);
	pthread_mutex_destroy(mutexes->eat);
	free(mutexes->print);
	free(mutexes->dead);
	free(mutexes->eat);
}

void	cleanup(t_data *data)
{
	data->dead = true;
	vec_free(data->philos);
	vec_free(data->mutexes.forks);
	clean_mutexes(&data->mutexes);
}

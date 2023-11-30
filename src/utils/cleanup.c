/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleanup.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/27 12:30:07 by mdekker       #+#    #+#                 */
/*   Updated: 2023/11/30 17:38:46 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philos.h>

// static void	clean_mutexes(t_mutexes *mutexes)
// {
// 	// pthread_mutex_destroy(print);
// 	// pthread_mutex_destroy(dead);
// 	// pthread_mutex_destroy(eat);
// 	free(print);
// 	free(dead);
// 	free(eat);
// }

void	cleanup(t_data *data)
{
	// (void)data;
	pthread_mutex_lock(&data->dead);
	data->is_dead = true;
	pthread_mutex_unlock(&data->dead);
	// clean_mutexes(&data->mutexes);
	exit(0);
}

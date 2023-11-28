/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/02 16:50:29 by mdekker       #+#    #+#                 */
/*   Updated: 2023/11/28 13:27:19 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philos.h>

void	free_philo(void *philo)
{
	t_philo	*tmp;

	tmp = (t_philo *)philo;
	pthread_mutex_destroy(tmp->lock);
	free(tmp->lock);
	// free(tmp);
}

void	print_philo(void *philo)
{
	t_philo	*tmp;

	tmp = (t_philo *)philo;
	printf("\033[1;34m|-- Philo Address: %p\033[0m\n", tmp);
	printf("\033[1;34m|---- ID: %ld\033[0m\n", tmp->id);
	printf("\033[1;34m|---- Eat count: %ld\033[0m\n", tmp->eat_count);
	printf("\033[1;34m|---- Philo lock address: %p\033[0m\n", tmp->lock);
}

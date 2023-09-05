/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/02 16:50:29 by mdekker       #+#    #+#                 */
/*   Updated: 2023/09/05 18:46:57 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philos.h>

void	free_philo(void *philo)
{
	free(philo);
}

void	print_philo(void *philo)
{
	t_philo	*tmp;

	tmp = (t_philo *)philo;
	printf("\033[1;34m|-- Philo Address: %p\033[0m\n", tmp);
	printf("\033[1;34m|---- ID: %ld\033[0m\n", tmp->id);
	printf("\033[1;34m|---- Eat count: %ld\033[0m\n", tmp->eat_count);
	printf("\033[1;34m|---- Data Address: %p\033[0m\n", tmp->data);
}

static size_t	start_diff(t_philo *philo)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return ((current.tv_sec * 1000 + current.tv_usec / 1000)
		- (philo->data->start.tv_sec * 1000 + philo->data->start.tv_usec
			/ 1000));
}

void	print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(philo->data->mutexes.print);
	printf("%ld %ld %s\n", start_diff(philo), philo->id + 1, status);
	pthread_mutex_unlock(philo->data->mutexes.print);
}

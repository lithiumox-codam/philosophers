/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/03 20:57:15 by mdekker       #+#    #+#                 */
/*   Updated: 2023/11/29 17:45:54 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philos.h>

bool	check_death(t_philo *philo)
{
	pthread_mutex_lock(philo->data->mutexes.dead);
	if (philo->data->dead)
		return (pthread_mutex_unlock(philo->data->mutexes.dead), true);
	pthread_mutex_unlock(philo->data->mutexes.dead);
	return (false);
}

bool	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (!print_status(philo, "has taken a fork"))
		return (pthread_mutex_unlock(philo->left_fork), false);
	pthread_mutex_lock(philo->right_fork);
	if (!print_status(philo, "has taken a fork"))
		return (drop_forks(philo), false);
	return (true);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

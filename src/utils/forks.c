/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   forks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/03 20:57:15 by mdekker       #+#    #+#                 */
/*   Updated: 2023/12/02 17:42:40 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philos.h>

/**
 * @brief Checks if a philosopher is dead by checking the is_dead flag
 *
 * @param philo The philosopher to access the data struct from
 * @return bool Whether the philosopher is dead
 */
bool	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->dead);
	if (philo->data->is_dead)
		return (pthread_mutex_unlock(&philo->data->dead), true);
	pthread_mutex_unlock(&philo->data->dead);
	return (false);
}

/**
 * @brief Takes the forks from the table
 *
 * @param philo The philosopher to take the forks
 * @return bool Whether the forks were taken successfully
 */
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

/**
 * @brief A wrapper function for dropping the forks
 *
 * @param philo The philosopher to drop the forks
 */
void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

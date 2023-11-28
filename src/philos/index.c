/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   index.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/03 21:04:17 by mdekker       #+#    #+#                 */
/*   Updated: 2023/11/28 16:41:09 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philos.h>

/**
 * @brief The eat state of the philosopher
 *
 * @param philo The philosopher
 * @param data The data struct
 */
static bool	philo_eat(t_philo *philo)
{
	take_forks(philo);
	if (!print_status(philo))
		return (drop_forks(philo), false);
	pthread_mutex_lock(philo->lock);
	philo->last_eaten = current_time();
	philo->eat_count++;
	if (philo->state == DEAD)
		return (pthread_mutex_unlock(philo->lock), drop_forks(philo), false);
	pthread_mutex_unlock(philo->lock);
	wait_for(philo, philo->data->time_to_eat);
	drop_forks(philo);
	pthread_mutex_lock(philo->lock);
	philo->state = SLEEPING;
	pthread_mutex_unlock(philo->lock);
	return (true);
}

/**
 * @brief The sleep state of the philosopher
 *
 * @param philo The philosopher
 * @param data The data struct
 */
static bool	philo_sleep(t_philo *philo)
{
	if (!print_status(philo))
		return (false);
	wait_for(philo, philo->data->time_to_sleep);
	pthread_mutex_lock(philo->lock);
	philo->state = THINKING;
	pthread_mutex_unlock(philo->lock);
	if (!print_status(philo))
		return (false);
	return (true);
}

/**
 * @brief The loop of the philosopher
 *
 * @param philo The philosopher
 * @param data The data struct
 */
void	philo_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->data->mutexes.start);
	pthread_mutex_unlock(philo->data->mutexes.start);
	if (philo->state == THINKING)
	{
		if (!print_status(philo))
			return ;
		wait_for(philo, philo->data->time_to_eat / 2);
	}
	while (1)
	{
		if (philo->eat_count == philo->data->eat_count)
			return ;
		if (philo->state == DEAD)
			return ;
		if (!philo_eat(philo))
			return ;
		if (!philo_sleep(philo))
			return ;
	}
	return (pthread_mutex_unlock(philo->lock),
		pthread_mutex_destroy(philo->lock), (void)NULL);
}

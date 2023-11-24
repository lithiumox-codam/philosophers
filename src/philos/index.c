/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   index.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/03 21:04:17 by mdekker       #+#    #+#                 */
/*   Updated: 2023/11/24 17:41:07 by mdekker       ########   odam.nl         */
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
	// Lock : Data races
	philo->last_eaten = current_time();
	philo->eat_count++;
	// Unlock
	wait_for(philo, philo->data->time_to_eat);
	drop_forks(philo);
	philo->state = SLEEPING;
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
	printf("time: %zu\n", philo->data->time_to_sleep);
	philo->state = THINKING;
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
	if (philo->state == THINKING)
	{
		if (!print_status(philo))
			return ;
		wait_for(philo, philo->data->time_to_eat / 2);
	}
	while (1)
	{
		if (!philo_eat(philo))
			return ;
		if (!philo_sleep(philo))
			return ;
		if (!print_status(philo))
			return ;
		if (philo->state == DEAD)
			return ;
	}
}

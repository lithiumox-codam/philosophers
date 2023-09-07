/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   index.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/03 21:04:17 by mdekker       #+#    #+#                 */
/*   Updated: 2023/09/07 23:10:52 by lithium       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philos.h>

/**
 * @brief The think state of the philosopher
 *
 * @param philo The philosopher
 * @param data The data struct
 */
static void	philo_think(t_philo *philo)
{
	print_status(philo);
	philo->state = EATING;
}

/**
 * @brief The eat state of the philosopher
 *
 * @param philo The philosopher
 * @param data The data struct
 */
static void	philo_eat(t_philo *philo)
{
	take_forks(philo);
	print_status(philo);
	philo->last_eaten = current_time();
	philo->eat_count++;
	wait_for(philo->data->time_to_eat);
	drop_forks(philo);
	philo->state = SLEEPING;
}

/**
 * @brief The sleep state of the philosopher
 *
 * @param philo The philosopher
 * @param data The data struct
 */
static void	philo_sleep(t_philo *philo)
{
	print_status(philo);
	wait_for(philo->data->time_to_sleep);
	philo->state = THINKING;
}

/**
 * @brief The loop of the philosopher
 *
 * @param philo The philosopher
 * @param data The data struct
 */
void	philo_loop(t_philo *philo)
{
	while (1)
	{
		if (philo->state == THINKING)
			philo_think(philo);
		else if (philo->state == EATING)
			philo_eat(philo);
		else if (philo->state == SLEEPING)
			philo_sleep(philo);
		else if (philo->state == DEAD)
			return ;
	}
}

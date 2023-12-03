/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/03 21:04:17 by mdekker       #+#    #+#                 */
/*   Updated: 2023/12/03 16:58:05 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philos.h>

/**
 * @brief A fuction that help create a waiting queue for the philosophers
 * so they dont grab forks immediately when they have enough time to live
 *
 * @param philo The philosopher to check
 */
static void	check_time_gap(t_philo *philo)
{
	size_t	time_gap;
	size_t	eat_diff;

	if (philo->data->start_time == philo->last_eaten)
		return ;
	pthread_mutex_lock(&philo->lock);
	time_gap = get_time() - philo->last_eaten;
	eat_diff = philo->data->time_to_die - philo->data->time_to_eat;
	if (time_gap < eat_diff)
		wait_for(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->lock);
}

/**
 * @brief The eat state of the philosopher
 *
 * @param philo The philosopher
 * @param data The data struct
 */
static bool	philo_eat(t_philo *philo)
{
	if (!take_forks(philo))
		return (false);
	if (!print_status(philo, "is eating"))
		return (drop_forks(philo), false);
	wait_for(philo->data->time_to_eat);
	drop_forks(philo);
	pthread_mutex_lock(&philo->lock);
	philo->last_eaten = get_time();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->lock);
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
	if (!print_status(philo, "is sleeping"))
		return (false);
	wait_for(philo->data->time_to_sleep);
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
	pthread_mutex_lock(&philo->data->start);
	pthread_mutex_unlock(&philo->data->start);
	if ((philo->id) % 2 == 0)
	{
		if (!print_status(philo, "is thinking"))
			return ;
		usleep((philo->data->time_to_eat / 2) * 1000);
	}
	while (1)
	{
		if (philo->data->philo_count == 3)
			check_time_gap(philo);
		if (!philo_eat(philo))
			return ;
		if (!philo_sleep(philo))
			return ;
		if (!print_status(philo, "is thinking"))
			return ;
	}
}

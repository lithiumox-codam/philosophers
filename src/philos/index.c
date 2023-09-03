/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   index.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/03 21:04:17 by mdekker       #+#    #+#                 */
/*   Updated: 2023/09/02 22:16:13 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philos.h>

/**
 * @brief The create function of the philosopher
 *
 * @param philo The philo vector
 * @param argc The amount of arguments
 * @param argv The arguments
 * @return bool The exit code
 */
bool	create_philos(t_vector *philo, t_data *data)
{
	t_philo	*philo_data;
	size_t	i;

	i = 0;
	while (i < data->philo_count)
	{
		philo_data = malloc(sizeof(t_philo));
		if (!philo_data)
			return (false);
		philo_data = create_philo(i, data);
		if (!vec_push(philo, philo_data))
			return (false);
		i++;
	}
	return (true);
}

/**
 * @brief The think state of the philosopher
 *
 * @param philo The philosopher
 * @param data The data struct
 */
static void	philo_think(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->mutexes.print);
	printf("%zu is thinking\n", philo->id);
	pthread_mutex_unlock(&data->mutexes.print);
	philo->state = EATING;
}

/**
 * @brief The eat state of the philosopher
 *
 * @param philo The philosopher
 * @param data The data struct
 */
static void	philo_eat(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->mutexes.print);
	printf("%zu is eating\n", philo->id);
	pthread_mutex_unlock(&data->mutexes.print);
	philo->last_eaten = current_time();
	philo->eat_count++;
	if (philo->eat_count == data->eat_count)
	{
		pthread_mutex_lock(&data->mutexes.eat_count);
		data->philo_eaten++;
		pthread_mutex_unlock(&data->mutexes.eat_count);
	}
	philo->state = SLEEPING;
}

/**
 * @brief The sleep state of the philosopher
 *
 * @param philo The philosopher
 * @param data The data struct
 */
static void	philo_sleep(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->mutexes.print);
	printf("%zu is sleeping\n", philo->id);
	pthread_mutex_unlock(&data->mutexes.print);
	philo->state = THINKING;
}

/**
 * @brief The loop of the philosopher
 *
 * @param philo The philosopher
 * @param data The data struct
 */
void	philo_loop(t_philo *philo, t_data *data)
{
	while (1)
	{
		if (philo->state == THINKING)
			philo_think(philo, data);
		else if (philo->state == EATING)
			philo_eat(philo, data);
		else if (philo->state == SLEEPING)
			philo_sleep(philo, data);
	}
}

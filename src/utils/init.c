/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/03 20:54:54 by mdekker       #+#    #+#                 */
/*   Updated: 2023/12/03 00:23:59 by lithium       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philos.h>

/**
 * @brief A helper function to initialize the mutexes that are globally used
 * and clean them up if the initialization of one fails
 *
 * @param mutexes The mutexes to initialize
 * @return bool Whether the initialization was successful
 */
static bool	init_and_clean_mutexes(t_data *data)
{
	size_t			i;
	size_t			j;
	pthread_mutex_t	*mutexes[4];

	i = 0;
	mutexes[0] = &data->print;
	mutexes[1] = &data->dead;
	mutexes[2] = &data->eat;
	mutexes[3] = &data->start;
	while (i < 4)
	{
		if (pthread_mutex_init(mutexes[i], NULL))
		{
			j = 0;
			while (j < i)
			{
				pthread_mutex_destroy(mutexes[j]);
				j++;
			}
			return (false);
		}
		i++;
	}
	return (true);
}

/**
 * @brief Initializes the mutexes
 *
 * @param data The data struct to initialize
 * @return bool Whether the initialization was successful
 */
static bool	initialize_mutexes(t_data *data)
{
	size_t	i;

	i = 0;
	if (!init_and_clean_mutexes(data))
		return (print_error("Mutex init fail!", NULL), false);
	data->forks = calloc(sizeof(pthread_mutex_t), (data->philo_count));
	if (!data->forks)
		return (print_error("Forks init fail!", NULL), false);
	while (i < data->philo_count)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
		{
			while (i > 0)
			{
				pthread_mutex_destroy(&data->forks[i]);
				i--;
			}
			return (print_error("Forks mutex init fail!", NULL), false);
		}
		i++;
	}
	return (true);
}

/**
 * @brief Assigns the forks to the philosopher
 *
 * @param philo The philosopher to assign the forks to
 * @note The first philosopher will have the right fork first
 * so there are no potential deadlocks
 */
static void	assign_forks(t_philo *philo)
{
	if (philo->id != 0)
	{
		philo->left_fork = &philo->data->forks[philo->id];
		philo->right_fork = &philo->data->forks[(philo->id + 1)
			% philo->data->philo_count];
	}
	else
	{
		philo->left_fork = &philo->data->forks[(philo->id + 1)
			% philo->data->philo_count];
		philo->right_fork = &philo->data->forks[philo->id];
	}
}

/**
 * @brief Initializes the philosophers
 *
 * @param data The data struct to initialize
 * @return bool Whether the initialization was successful
 */
static bool	init_philos(t_data *data)
{
	t_philo	*philo;

	data->philos = malloc(sizeof(t_philo) * data->philo_count);
	if (!data->philos)
		return (false);
	while (data->philos_created < data->philo_count)
	{
		philo = &data->philos[data->philos_created];
		philo->id = data->philos_created;
		philo->data = data;
		philo->eat_count = 0;
		pthread_mutex_init(&data->philos[data->philos_created].lock, NULL);
		assign_forks(philo);
		data->philos_created++;
	}
	return (true);
}

/**
 * @brief The function to initialize all used vectors & mutexes
 *
 * @param data The data struct to initialize
 * @return bool Whether the initialization was successful
 */
bool	init(t_data *data, int ac, char **av)
{
	if (!parse_input(data, ac, av))
		return (false);
	if (!initialize_mutexes(data))
		return (false);
	if (!init_philos(data))
		return (false);
	return (true);
}

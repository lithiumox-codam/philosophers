/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/03 14:08:36 by mdekker       #+#    #+#                 */
/*   Updated: 2023/12/17 15:54:32 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philos.h>

/**
 * @brief A helper function for the die mechanism so the program can exit
 *
 * @param data
 * @param i
 */
static void	die_helper(t_data *data, size_t i)
{
	pthread_mutex_lock(&data->dead);
	data->is_dead = true;
	pthread_mutex_unlock(&data->dead);
	pthread_mutex_lock(&data->print);
	printf("%zu %zu died\n", curr_time_diff(data->start_time),
		data->philos[i].id + 1);
	pthread_mutex_unlock(&data->print);
	close_all(data);
	cleanup(data);
}

/**
 * @brief A helper function for the eat mechanism so the program can exit
 *
 * @param data The data struct
 */
static void	eat_helper(t_data *data)
{
	pthread_mutex_lock(&data->dead);
	data->is_dead = true;
	pthread_mutex_unlock(&data->dead);
	close_all(data);
	cleanup(data);
}

/**
 * @brief The monitor function that checks if the philosophers are still alive
 * and if the eat count has been reached by all philosophers if applicable
 *
 * @param data The data struct
 */
static void	monitor(t_data *data)
{
	size_t	i;

	while (1)
	{
		i = 0;
		while (i < data->philo_count)
		{
			pthread_mutex_lock(&philo->lock);
			if (data->eat_count != 0
				&& data->philos[i].eat_count == data->eat_count)
				data->philos_eaten++;
			pthread_mutex_unlock(&philo->lock);
			if (!die_time_check(&data->philos[i]))
				return (die_helper(data, i));
			if (data->eat_count != 0 && data->philos_eaten == data->philo_count)
				return (eat_helper(data));
			i++;
		}
		usleep(1000);
	}
}

/**
 * @brief The function that runs the simulation and creates the threads
 *
 * @param data The data struct
 */
void	run_simulation(t_data *data)
{
	size_t	i;

	i = 0;
	pthread_mutex_lock(&data->start);
	while (i < data->philo_count)
	{
		if (pthread_create(&data->philos[i].thread, NULL, (void *)philo_loop,
				(void *)&data->philos[i]) != 0)
			return (print_error("Failed to create threads", NULL),
				kill_created_philos(data, i), cleanup(data));
		i++;
	}
	if (data->philo_count == 1)
		return (singular_philo(data), cleanup(data));
	data->start_time = get_time();
	i = 0;
	while (i < data->philo_count)
	{
		data->philos[i].last_eaten = data->start_time;
		i++;
	}
	pthread_mutex_unlock(&data->start);
	monitor(data);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac < 5 || ac > 6)
		return (print_error("Wrong amount of arguments", NULL), 1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (print_error("Data malloc failed!", NULL), 1);
	memset(data, 0, sizeof(t_data));
	if (!init(data, ac, av))
		return (free(data), 1);
	run_simulation(data);
	free(data);
	return (0);
}

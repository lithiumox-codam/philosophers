/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/03 20:54:54 by mdekker       #+#    #+#                 */
/*   Updated: 2023/09/02 16:17:43 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philos.h>

void	*push_mutexes(t_vector *vec, size_t count)
{
	size_t			i;
	pthread_mutex_t	*mutex;

	i = 0;
	while (i < count)
	{
		mutex = malloc(sizeof(pthread_mutex_t));
		if (!mutex || !vec_push(vec, mutex))
			return (NULL);
		i++;
	}
	return (vec->data);
}

static bool	check_input(t_data *data, int ac)
{
	if (data->philo_count == 0 || data->philo_count > 200)
		return (false);
	if (data->time_to_die == 0 || data->time_to_die > 2147483647)
		return (false);
	if (data->time_to_eat == 0 || data->time_to_eat > 2147483647)
		return (false);
	if (data->time_to_sleep == 0 || data->time_to_sleep > 2147483647)
		return (false);
	if (ac > 5 && (data->eat_count == 0 || data->eat_count > 2147483647))
		return (false);
	return (true);
}

/**
 * @brief Checks if the input is valid
 *
 * @param ac The amount of arguments
 * @param av The arguments
 * @return true When the input is valid
 * @return false When the input is invalid
 */
static bool	check_strings(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if ((av[i][j] >= '0' && av[i][j] <= '9') || j > 10)
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

static bool	parse_input(t_data *data, int ac, char **av)
{
	if (check_strings(ac, av))
		return (false);
	data->philo_count = atost(av[1]);
	data->time_to_die = atost(av[2]);
	data->time_to_eat = atost(av[3]);
	data->time_to_sleep = atost(av[4]);
	if (ac == 6)
		data->eat_count = atost(av[5]);
	return (check_input(data, ac));
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
		return (printf("ERROR: Wrong input\n"), false);
	return (true);
}

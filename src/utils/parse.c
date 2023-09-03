/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/02 22:57:32 by mdekker       #+#    #+#                 */
/*   Updated: 2023/09/02 23:00:25 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philos.h>

void	print_error(char *error_msg)
{
	printf("\033[1;31mERROR: %s\033[0m\n", error_msg);
}

static bool	check_input(t_data *data, int ac)
{
	if (data->philo_count == 0 || data->philo_count > 200)
		return (print_error("Philo maximum is 200"), false);
	if (data->time_to_die == 0 || data->time_to_die > 2147483647)
		return (print_error("Invalid time to die"), false);
	if (data->time_to_eat == 0 || data->time_to_eat > 2147483647)
		return (print_error("Invalid time to eat"), false);
	if (data->time_to_sleep == 0 || data->time_to_sleep > 2147483647)
		return (print_error("Invalid time to sleep"), false);
	if (ac > 5 && (data->eat_count > 2147483647))
		return (print_error("Invalid number of times to eat"), false);
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

bool	parse_input(t_data *data, int ac, char **av)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/02 22:57:32 by mdekker       #+#    #+#                 */
/*   Updated: 2023/12/02 20:27:00 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philos.h>

void	print_error(char *error_msg, bool *error)
{
	printf("\033[1;31mERROR: %s\033[0m\n", error_msg);
	if (error)
		*error = false;
}

/**
 * @brief Basic bounds checker for the various input values
 *
 * @param data The data struct
 * @param ac The amount of arguments
 * @return true When the input is valid
 * @return false When the input is invalid
 */
static bool	check_input(t_data *data, int ac)
{
	bool	no_error;

	no_error = true;
	if (data->philo_count == 0 || data->philo_count > 200)
		print_error("Philo maximum is 200", &no_error);
	if (data->time_to_die == 0 || data->time_to_die > 2147483647)
		print_error("Invalid time to die", &no_error);
	if (data->time_to_eat == 0 || data->time_to_eat > 2147483647)
		print_error("Invalid time to eat", &no_error);
	if (data->time_to_sleep == 0 || data->time_to_sleep > 2147483647)
		print_error("Invalid time to sleep", &no_error);
	if (ac > 5 && ((data->eat_count > 2147483647) || data->eat_count == 0))
		print_error("Invalid number of times to eat", &no_error);
	return (no_error);
}

/**
 * @brief Checks if the input is valid
 *
 * @note Checks if the string is not too long
 * and if the string only contains numbers as
 * to not trip up atost()
 *
 * @param ac The amount of arguments
 * @param av The arguments
 * @return true When the input is valid
 * @return false When the input is invalid
 */
static bool	check_strings(int ac, char **av)
{
	int		i;
	int		j;
	char	*str;

	str = "Numeric arguments only!";
	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (!(av[i][j] >= '0' && av[i][j] <= '9'))
				return (print_error(str, NULL), false);
			j++;
		}
		i++;
	}
	return (true);
}

/**
 * @brief Parses the input and stores it in the data struct
 * Checks will be done before the program starts to run
 * to prevent wasting time
 *
 * @param data The data struct
 * @param ac The amount of arguments
 * @param av The arguments
 * @return true When the input is valid
 * @return false When the input is invalids
 */
bool	parse_input(t_data *data, int ac, char **av)
{
	if (!check_strings(ac, av))
		return (false);
	data->philo_count = atost(av[1]);
	data->time_to_die = atost(av[2]);
	data->time_to_eat = atost(av[3]);
	data->time_to_sleep = atost(av[4]);
	data->is_dead = false;
	if (ac == 6)
		data->eat_count = atost(av[5]);
	return (check_input(data, ac));
}

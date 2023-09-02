/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   index.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/03 21:04:17 by mdekker       #+#    #+#                 */
/*   Updated: 2023/09/02 16:54:13 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philos.h>

/**
 * @brief The main function of the philosopher
 *
 * @param philo The philo vector
 * @param argc The amount of arguments
 * @param argv The arguments
 * @return bool The exit code
 */
bool	create_philos(t_vector *philo, size_t philo_count, t_data *data)
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
	}
	return (true);
}

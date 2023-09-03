/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/03 14:08:36 by mdekker       #+#    #+#                 */
/*   Updated: 2023/09/03 22:55:29 by lithium       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philos.h>

void	run_simulation(t_data *data)
{
	size_t	i;
	t_philo	*philo;

	i = 0;
	while (i < data->philo_count)
	{
		philo = vec_get(data->philos, i);
		if (pthread_create(&philo->thread, NULL, (void *)philo_loop,
				philo) != 0)
			return (print_error("Failed to create thread"));
		i++;
	}
	i = 0;
	while (i < data->philo_count)
	{
		philo = vec_get(data->philos, i);
		if (pthread_join(philo->thread, NULL) != 0)
			return (print_error("Failed to join thread"));
		i++;
	}
}

int	main(int ac, char **av)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	if (ac < 5 || ac > 6)
		return (print_error("Wrong amount of arguments"), 1);
	if (!init(&data, ac, av))
		return (1);
	print_vec(data.mutexes.forks, print_mutex);
	print_vec(data.philos, print_philo);
	printf("Running SIMULATION\n");
	run_simulation(&data);
	printf("Simulation done\n");
	return (0);
}

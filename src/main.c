/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/03 14:08:36 by mdekker       #+#    #+#                 */
/*   Updated: 2023/11/24 17:24:08 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philos.h>

static void	monitor(t_vector *philos)
{
	size_t	i;
	t_philo	*philo;

	i = 0;
	while (true)
	{
		while (i < philos->length)
		{
			philo = (t_philo *)vec_get(philos, i);
			if (!die_time_check(philo->last_eaten, philo))
			{
				printf("%zu %zu died\n", start_diff(philo), philo->id + 1);
				return ;
			}
			if (philo->eat_count < philo->data->eat_count)
				return ;
			i++;
		}
		i = 0;
		usleep(500);
	}
	printf("All philosophers have eaten %zu times\n", philo->data->eat_count);
}

void	run_simulation(t_data *data)
{
	size_t	i;
	t_philo	*philo;

	i = 0;
	data->start = current_time();
	while (i < data->philo_count)
	{
		philo = (t_philo *)vec_get(data->philos, i);
		if (pthread_create(&philo->thread, NULL, (void *)philo_loop,
				philo) != 0)
			return (print_error("Failed to create thread"));
		i++;
	}
	i = 0;
	monitor(data->philos);
	while (i < data->philo_count)
	{
		philo = (t_philo *)vec_get(data->philos, i);
		if (pthread_join(philo->thread, NULL) != 0)
			return (print_error("Failed to join thread"));
		i++;
	}
}

int	main(int ac, char **av)
{
	t_data	data;

	ft_memset(&data, 0, sizeof(t_data));
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

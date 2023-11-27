/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/03 14:08:36 by mdekker       #+#    #+#                 */
/*   Updated: 2023/11/27 13:31:20 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philos.h>

// static void	close_all(t_vector *philos)
// {
// 	size_t	i;
// 	t_philo	*philo;

// 	i = 0;
// 	printf("amount of philos: %zu\n", philos->length);
// 	while (i < philos->length)
// 	{
// 		philo = (t_philo *)vec_get(philos, i);
// 		if (philo->thread)
// 			pthread_join(philo->thread, NULL);
// 		i++;
// 	}
// }

static void	monitor(t_vector *philos)
{
	size_t	i;
	t_philo	*philo;

	i = 0;
	while (!philo->data->dead)
	{
		while (i < philos->length)
		{
			philo = (t_philo *)vec_get(philos, i);
			if (!die_time_check(philo->last_eaten, philo))
			{
				pthread_mutex_lock(philo->data->mutexes.print);
				printf("%zu %zu died\n", start_diff(philo), philo->id + 1);
				print_vec(philo->data->mutexes.forks, print_mutex);
				close_all(philos); // TODO: fix this
				cleanup(philo->data);
				// Commented out currently treads not properly joined
				return ;
			}
			i++;
		}
		i = 0;
		usleep(500);
	}
	pthread_mutex_unlock(philo->data->mutexes.print);
	printf("All philosophers have eaten %zu times\n", philo->data->eat_count);
	pthread_mutex_unlock(philo->data->mutexes.print);
	close_all(philos);
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
	run_simulation(&data);
	printf("Simulation done\n");
	return (0);
}

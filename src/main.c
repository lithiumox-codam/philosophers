/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/03 14:08:36 by mdekker       #+#    #+#                 */
/*   Updated: 2023/11/28 16:37:34 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philos.h>

static void	close_all(t_vector *philos)
{
	size_t	i;
	t_philo	*philo;

	i = 0;
	while (i < philos->length)
	{
		philo = (t_philo *)vec_get(philos, i);
		if (philo->thread)
			pthread_join(philo->thread, NULL);
		free_philo(philo);
		i++;
	}
}

static void	monitor(t_vector *philos)
{
	size_t	i;
	t_philo	*philo;

	i = 0;
	while (1)
	{
		usleep(500);
		while (i < philos->length)
		{
			philo = (t_philo *)vec_get(philos, i);
			if (!die_time_check(philo->last_eaten, philo))
			{
				pthread_mutex_lock(philo->data->mutexes.print);
				printf("%zu %zu died\n", start_diff(philo), philo->id + 1);
				pthread_mutex_unlock(philo->data->mutexes.print);
				print_vec(philo->data->mutexes.forks, print_mutex);
				close_all(philos);
				cleanup(philo->data);
				return ;
			}
			i++;
		}
		i = 0;
	}
	pthread_mutex_unlock(philo->data->mutexes.print);
	printf("All philosophers have eaten %zu times\n", philo->data->eat_count);
	pthread_mutex_unlock(philo->data->mutexes.print);
}

void	run_simulation(t_data *data)
{
	size_t	i;
	t_philo	*philo;

	i = 0;
	pthread_mutex_lock(data->mutexes.start);
	while (i < data->philo_count)
	{
		philo = (t_philo *)vec_get(data->philos, i);
		if (pthread_create(&philo->thread, NULL, (void *)philo_loop,
				philo) != 0)
			return (print_error("Failed to create thread"));
		i++;
	}
	data->start = current_time();
	i = 0;
	while (i < data->philo_count)
	{
		philo = (t_philo *)vec_get(data->philos, i);
		philo->last_eaten = data->start;
		i++;
	}
	pthread_mutex_unlock(data->mutexes.start);
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

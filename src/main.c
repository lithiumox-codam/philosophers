/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/03 14:08:36 by mdekker       #+#    #+#                 */
/*   Updated: 2023/11/30 20:22:47 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philos.h>

static void	close_all(t_data *data)
{
	size_t	i;

	// t_philo	*philo;
	i = 0;
	while (i < data->philo_count)
	{
		// if (data->philos[i]->thread)
		pthread_join(data->philos[i].thread, NULL);
		// free_philo(data->philos[i]);
		i++;
	}
}

static void	change_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->dead);
	philo->data->is_dead = true;
	pthread_mutex_unlock(&philo->data->dead);
}

static void	monitor(t_data *data)
{
	size_t	i;

	while (1)
	{
		i = 0;
		while (i < data->philo_count)
		{
			if (!die_time_check(&data->philos[i]))
			{
				change_death(&data->philos[i]);
				pthread_mutex_lock(&data->print);
				printf("%zu %zu died\n", curr_time_diff(data->start_time),
					data->philos[i].id + 1);
				pthread_mutex_unlock(&data->print);
				close_all(data);
				cleanup(data);
				return ;
			}
			i++;
		}
		usleep(1000);
	}
	// pthread_mutex_unlock(philos[i]->data->print);
	// printf("All philosophers have eaten %zu times\n",
	// 	philos[i]->data->eat_count);
	// pthread_mutex_unlock(philos[i]->data->print);
}

void	run_simulation(t_data *data)
{
	size_t	i;

	// t_philo	*philo;
	i = 0;
	pthread_mutex_lock(&data->start);
	while (i < data->philo_count)
	{
		if (pthread_create(&data->philos[i].thread, NULL, (void *)philo_loop,
				(void *)&data->philos[i]) != 0)
			return (print_error("Failed to create thread", NULL));
		i++;
	}
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

	memset(&data, 0, sizeof(t_data));
	data = malloc(sizeof(t_data));
	//   data.mutexes = calloc(1, sizeof(t_mutexes));
	data->is_dead = false;
	if (ac < 5 || ac > 6)
		return (print_error("Wrong amount of arguments", NULL), 1);
	if (!init(data, ac, av))
		return (1);
	run_simulation(data);
	printf("Simulation done\n");
	return (0);
}

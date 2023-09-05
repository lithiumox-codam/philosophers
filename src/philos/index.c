/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   index.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/03 21:04:17 by mdekker       #+#    #+#                 */
/*   Updated: 2023/09/04 17:39:44 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philos.h>

/**
 * @brief The time in ms since the start of the program
 *
 */
static struct timeval	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time);
}

/**
 * @brief A function to wait for a certain amount of time
 *
 */
static void	wait_ms(long ms)
{
	struct timeval	start;
	struct timeval	current;
	long			time_elapsed;

	start = get_time();
	while (1)
	{
		current = get_time();
		time_elapsed = (current.tv_sec * 1000 + current.tv_usec / 1000)
			- (start.tv_sec * 1000 + start.tv_usec / 1000);
		if (time_elapsed >= ms)
			return ;
	}
}

/**
 * @brief The think state of the philosopher
 *
 * @param philo The philosopher
 * @param data The data struct
 */
static void	philo_think(t_philo *philo)
{
	t_data	*tmp;

	tmp = philo->data;
	pthread_mutex_lock(tmp->mutexes.print);
	print_status(philo, "is thinking");
	pthread_mutex_unlock(tmp->mutexes.print);
	wait_ms(tmp->time_to_sleep);
	philo->state = EATING;
}

/**
 * @brief The eat state of the philosopher
 *
 * @param philo The philosopher
 * @param data The data struct
 */
static void	philo_eat(t_philo *philo)
{
	t_data	*tmp;

	tmp = philo->data;
	if (philo->state == DEAD)
	{
		pthread_mutex_lock(tmp->mutexes.print);
		printf("%zu has died\n", philo->id);
		pthread_mutex_unlock(tmp->mutexes.print);
		return ;
	}
	pthread_mutex_lock(tmp->mutexes.print);
	print_status(philo, "is eating");
	pthread_mutex_unlock(tmp->mutexes.print);
	philo->last_eaten = get_time();
	philo->eat_count++;
	wait_ms(tmp->time_to_eat);
	philo->state = SLEEPING;
}

/**
 * @brief The sleep state of the philosopher
 *
 * @param philo The philosopher
 * @param data The data struct
 */
static void	philo_sleep(t_philo *philo)
{
	t_data	*tmp;

	tmp = philo->data;
	pthread_mutex_lock(tmp->mutexes.print);
	print_status(philo, "is sleeping");
	pthread_mutex_unlock(tmp->mutexes.print);
	wait_ms(tmp->time_to_sleep);
	philo->state = THINKING;
}

static bool	check_start(t_data *data)
{
	size_t	created;

	pthread_mutex_lock(data->mutexes.philos_created);
	created = data->philos_created;
	pthread_mutex_unlock(data->mutexes.philos_created);
	if
		"P{cv b                    }"
}

/**
 * @brief The loop of the philosopher
 *
 * @param philo The philosopher
 * @param data The data struct
 */
void	philo_loop(t_philo *philo)
{
	if (!check_start(philo->data))
		return ;
	while (1)
	{
		if (philo->state == THINKING)
			philo_think(philo);
		else if (philo->state == EATING)
			philo_eat(philo);
		else if (philo->state == SLEEPING)
			philo_sleep(philo);
	}
}

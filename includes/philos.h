/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philos.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/03 13:49:11 by mdekker       #+#    #+#                 */
/*   Updated: 2023/09/03 22:50:24 by lithium       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOS_H
# define PHILOS_H

# include "vector.h"
# include <pthread.h>
# include <semaphore.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

/**
 * @brief The struct containing all mutexes
 *
 * @param forks The mutexes representing the forks
 * @param print The mutex used for printing
 * @param dead_mutex The mutex used to check if a philosopher has died
 * @param eat_mutex The mutex used to check if a philosopher has eaten
 * @param eat_count_mutex The mutex used to check if a philosopher has eaten
 * enough
 * @note The mutexes are stored in a vector, so they can be accessed by id
 */
typedef struct s_mutexes
{
	t_vector		*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	dead;
	pthread_mutex_t	eat;
	pthread_mutex_t	eat_count;
}					t_mutexes;
/**
 * @brief The struct containing all data needed for the program
 *
 * @param philo_count The amount of philosophers
 * @param time_to_die The time in ms after which a philosopher dies
 * @param time_to_eat The time in ms a philosopher takes to eat
 * @param time_to_sleep The time in ms a philosopher takes to sleep
 * @param eat_count The amount of times a philosopher needs to eat before
 * stopping (0 = infinite)
 * @param dead Whether a philosopher has died
 * @param philo_eaten The amount of times a philosopher has eaten
 * @param forks The mutexes representing the forks
 * @param print The mutex used for printing
 * @param dead_mutex The mutex used to check if a philosopher has died
 * @param eat_mutex The mutex used to check if a philosopher has eaten
 * @param eat_count_mutex The mutex used to check if a philosopher has eaten
 * enough
 * @param start The time at which the program started
 * @note The mutexes are stored in a vector, so they can be accessed by id
 * this is done to prevent having to pass the mutexes to every function
 */
typedef struct s_data
{
	size_t			philo_count;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			eat_count;
	size_t			dead;
	size_t			philo_eaten;
	t_vector		*philos;
	t_mutexes		mutexes;
	struct timeval	start;
}					t_data;

/**
 * @brief The enum containing all states a philosopher can be in
 *
 * @param THINKING The philosopher is thinking
 * @param EATING The philosopher is eating
 * @param SLEEPING The philosopher is sleeping
 * @param DEAD The philosopher is dead
 */
typedef enum e_state
{
	THINKING,
	EATING,
	SLEEPING,
	DEAD
}					t_state;

/**
 * @brief The struct containing all data needed for a philosopher
 *
 * @param id The id of the philosopher
 * @param state The state of the philosopher
 * @param thread The thread of the philosopher
 * @param left_fork The mutex of the left fork
 * @param right_fork The mutex of the right fork
 * @param last_eaten The time at which the philosopher last ate
 * @note The mutexes are stored in a vector, so they can be accessed by id
 */
typedef struct s_philo
{
	size_t			id;
	t_state			state;
	size_t			eat_count;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct timeval	last_eaten;
	t_data			*data;
}					t_philo;

/**
 * Functions
 */
void				philo_loop(t_philo *philo, t_data *data);
size_t				atost(char *str);
bool				init(t_data *data, int ac, char **av);
bool				parse_input(t_data *data, int ac, char **av);
void				print_error(char *error_msg);
void				free_mutex(void *mutexes);
void				free_philo(void *philo);

/**
 * Time functions
 */
struct timeval		current_time(void);
size_t				time_diff(struct timeval start, struct timeval end);

/**
 * Debug functions
 */
void				print_vec(t_vector *vec, void (*print)(void *));
void				print_mutex(void *mutex);
void				print_philo(void *philo);

#endif

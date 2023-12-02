/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philos.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/03 13:49:11 by mdekker       #+#    #+#                 */
/*   Updated: 2023/12/03 00:00:50 by lithium       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOS_H
# define PHILOS_H

# include <pthread.h>
# include <semaphore.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define DEBUG false

typedef struct s_data	t_data;

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
	size_t				id;
	size_t				eat_count;
	pthread_t			thread;
	pthread_mutex_t		lock;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	size_t				last_eaten;
	t_data				*data;
}						t_philo;

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
 * @param start The time at which the program started
 * @note The mutexes are stored in a vector, so they can be accessed by id
 * this is done to prevent having to pass the mutexes to every function
 */
typedef struct s_data
{
	size_t				philo_count;
	size_t				philos_created;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	size_t				eat_count;
	bool				eatcap;
	bool				is_dead;
	size_t				philos_eaten;
	t_philo				*philos;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print;
	pthread_mutex_t		dead;
	pthread_mutex_t		eat;
	pthread_mutex_t		start;
	size_t				start_time;
}						t_data;

/**
 * Functions
 */
void					philo_loop(t_philo *philo);
void					singular_philo(t_data *data);
size_t					atost(char *str);
bool					init(t_data *data, int ac, char **av);
bool					parse_input(t_data *data, int ac, char **av);
void					print_error(char *error_msg, bool *error);
bool					print_status(t_philo *philo, char *msg);
size_t					start_diff(t_philo *philo);
bool					take_forks(t_philo *philo);
void					drop_forks(t_philo *philo);
void					cleanup(t_data *data);
bool					check_death(t_philo *philo);
void					close_all(t_data *data);
void					kill_created_philos(t_data *data, size_t i);

/**
 * Time functions
 */
size_t					get_time(void);
size_t					curr_time_diff(size_t stamp);
void					wait_for(size_t time);
bool					die_time_check(t_philo *philo);

#endif

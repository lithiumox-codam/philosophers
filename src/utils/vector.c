/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/03 20:57:15 by mdekker       #+#    #+#                 */
/*   Updated: 2023/09/02 22:49:04 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philos.h>

/**
 * @brief Gets the id of the philosopher by subtracting the address of the vec
 * from the address of the provided philosopher struct
 *
 * @param ptr The address of the philosopher struct
 * @param vec The vector containing the philosophers
 * @return size_t The id of the philosopher
 *
 * @note When the vector is empty or NULL, -1 is returned
 */
size_t	philo_id(void *ptr, t_vector *vec)
{
	size_t	id;

	if (vec->length == 0 || vec->data == NULL)
		return (-1);
	id = (size_t)((t_philo *)ptr - (t_philo *)vec->data);
	return (id);
}

/**
 * @brief Gets the philosopher struct from the vector by adding the id to the
 * address of the vector
 *
 * @param id The id of the philosopher
 * @param vec The vector containing the philosophers
 * @return t_philo* The philosopher struct
 *
 * @note When the vector is empty or NULL, NULL is returned
 */
t_philo	*philo_from_id(size_t id, t_vector *vec)
{
	t_philo	*philo;

	if (vec->length == 0 || vec->data == NULL)
		return (NULL);
	philo = (t_philo *)(vec->data + id * vec->type_size);
	return (philo);
}

/**
 * @brief Gets the left fork of the philosopher
 *
 * @param philo The philosopher
 * @param data The data struct
 * @return pthread_mutex_t* The left fork
 */
pthread_mutex_t	*get_left_fork(t_philo *philo, t_data *data)
{
	if (philo->id == 0)
		return (vec_get(data->mutexes.forks, data->philo_count - 1));
	return (vec_get(data->mutexes.forks, philo->id - 1));
}

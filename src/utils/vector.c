/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/03 20:57:15 by mdekker       #+#    #+#                 */
/*   Updated: 2023/09/08 14:24:57 by mdekker       ########   odam.nl         */
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
		return (0);
	id = (size_t)((t_philo *)ptr - (t_philo *)vec->data);
	return (id + 1);
}

void	take_forks(t_philo *philo)
{
	t_vector	*p;

	p = philo->data->philos;
	pthread_mutex_lock(philo->left_fork);
	printf("%zu %zu has taken a fork\n", start_diff(philo), philo_id(philo, p));
	pthread_mutex_lock(philo->right_fork);
	printf("%zu %zu has taken a fork\n", start_diff(philo), philo_id(philo, p));
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

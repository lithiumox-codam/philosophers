/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/03 20:57:15 by mdekker       #+#    #+#                 */
/*   Updated: 2023/09/05 18:46:33 by mdekker       ########   odam.nl         */
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

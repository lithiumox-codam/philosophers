/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vec_init.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/15 22:19:09 by mdekker       #+#    #+#                 */
/*   Updated: 2023/07/22 16:38:19 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <vector.h>

/**
 * @brief Initializes a vector
 *
 * @param vec The vector to initialize
 * @param capacity The initial size of the vector
 * @param type_size The size of the content of the vector
 * @return void * The initialized vector or NULL if malloc fails
 */
void	*vec_init(t_vector *vec, size_t capacity, size_t type_size,
		void (*free_data)(void *))
{
	vec->data = malloc(capacity * type_size);
	if (!vec->data)
		return (NULL);
	vec->length = 0;
	vec->capacity = capacity;
	vec->type_size = type_size;
	vec->free = free_data;
	return (vec);
}

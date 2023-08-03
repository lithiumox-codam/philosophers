/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vec_push.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/15 22:26:05 by mdekker       #+#    #+#                 */
/*   Updated: 2023/07/24 09:48:41 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <vector.h>

/**
 * @brief Pushes data to the end of the vector
 *
 * @param vec The vector to push to
 * @param data The data to push
 * @return bool true when succeeded, false when failed
 */
bool	vec_push(t_vector *vec, void *data)
{
	if (vec->length == vec->capacity)
		if (vec_resize(vec, vec->capacity * 2) == false)
			return (false);
	ft_memcpy(vec->data + vec->length * vec->type_size, data, vec->type_size);
	vec->length++;
	free(data);
	return (true);
}

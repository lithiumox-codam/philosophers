/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vec_resize.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/18 21:55:06 by mdekker       #+#    #+#                 */
/*   Updated: 2023/07/24 09:44:03 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <vector.h>

/**
 * @brief Resizes the vector
 *
 * @warning If the new size is smaller than the current size, the data
 * will be lost for the elements that are removed from the vector are
 * not freed. Watch out for memory leaks! 🚰
 *
 *
 * @param vec The vector to resize
 * @param new_length The new size of the vector
 * @return bool true if the resize was successful, false if not
 */
bool	vec_resize(t_vector *vec, size_t new_length)
{
	void	*new;

	if (new_length == 0 || new_length < vec->length)
		return (false);
	new = ft_realloc(vec->data, new_length * vec->type_size);
	if (!new)
		return (false);
	vec->data = new;
	vec->capacity = new_length;
	return (true);
}

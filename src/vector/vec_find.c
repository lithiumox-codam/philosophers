/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vec_find.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/21 02:41:44 by mdekker       #+#    #+#                 */
/*   Updated: 2023/07/28 17:55:30 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <vector.h>

static t_found	*create_struct(void *data, size_t index)
{
	t_found	*found;

	found = malloc(sizeof(t_found));
	if (!found)
		return (NULL);
	found->item = data;
	found->index = index;
	return (found);
}

static void	emergency_free(t_found **found, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		free(found[i]);
		i++;
	}
	free(found);
}

static bool	find_matches(t_vector *vec, bool (*cmp)(void *), t_found **found)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < vec->length)
	{
		if (cmp(vec->data + i * vec->type_size) == true)
		{
			found[j] = create_struct(vec->data + i * vec->type_size, i);
			if (!found[j])
				return (emergency_free(found, j), false);
			j++;
		}
		i++;
	}
	found[j] = NULL;
	return (true);
}

/**
 * @brief Finds the all occurences of a comparison in the vector
 *
 * @param vec The vector to search in
 * @param cmp The function to compare the data
 * @return t_found** A list of found items with their index in the vector,
 * ending with NULL or NULL when failed
 */
t_found	**vec_find(t_vector *vec, bool (*cmp)(void *))
{
	size_t	count;
	t_found	**found;

	count = vec_count(vec, cmp);
	if (count == 0)
		return (NULL);
	found = malloc(sizeof(t_found *) * (count + 1));
	if (!found)
		return (NULL);
	count = 0;
	find_matches(vec, cmp, found);
	return (found);
}

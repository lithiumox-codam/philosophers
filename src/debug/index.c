/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   index.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/02 22:08:43 by mdekker       #+#    #+#                 */
/*   Updated: 2023/09/03 22:40:19 by lithium       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philos.h>

void	print_vec(t_vector *vec, void (*print)(void *))
{
	size_t	i;

	i = 0;
	while (i < vec->length)
	{
		print(vec_get(vec, i));
		i++;
	}
}

void	print_mutex(void *mutex)
{
	printf("\033[1;34m|-- Mutex Address: %p\033[0m\n", mutex);
}
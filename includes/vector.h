/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/15 22:20:37 by mdekker       #+#    #+#                 */
/*   Updated: 2023/09/05 18:41:00 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <stdbool.h>
# include <stdlib.h>

/**
 * @brief A struct to store the found data and index so it can be returned
 *
 * @param item The found data
 * @param index The index of the found data
 *
 * @note This struct is only used in vec_find so the user doesn't have to
 * call the other functions to get the index of the found data
 */
typedef struct s_found
{
	void	*item;
	size_t	index;
}			t_found;

/**
 * @brief A vector struct
 *
 * @param data The data of the vector
 * @param length The current length of the vector
 * @param type_size The size of the content of the vector
 * @param capacity The current capacity of the vector
 * @param free The function to free the data of the vector
 * @return void
 *
 */
typedef struct s_vector
{
	void	*data;
	size_t	length;
	size_t	type_size;
	size_t	capacity;
	void	(*free)(void *);
}			t_vector;

void		*vec_init(t_vector *vec, size_t capacity, size_t type_size,
				void (*free)(void *));
void		*vec_get(t_vector *vec, size_t index);
void		*vec_set(t_vector *vec, size_t index, void *data);
void		*vec_pop(t_vector *vec);
void		*vec_remove(t_vector *v, size_t i);
t_found		**vec_find(t_vector *vec, bool (*cmp)(void *));
void		*vec_replace(t_vector *vec, size_t index, void *data);
void		vec_apply(t_vector *vec, void (*f)(void *));
void		vec_free(t_vector *vec);
bool		vec_insert(t_vector *v, size_t i, void *data);
bool		vec_push(t_vector *vec, void *data);
bool		vec_resize(t_vector *vec, size_t new_size);
size_t		vec_count(t_vector *vec, bool (*f)(void *));

/**
 * Mini selection of libft functions to make the vector work
 */
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memset(void *b, int c, size_t len);
void		*ft_realloc(void *ptr, size_t size);
#endif

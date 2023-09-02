/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   atost.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/02 14:55:35 by mdekker       #+#    #+#                 */
/*   Updated: 2023/09/02 15:05:40 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philos.h>

/**
 * @brief Converts a string to a size_t
 *
 * @param str The string to convert
 * @return size_t The converted string
 */
size_t	atost(char *str)
{
	size_t	i;
	size_t	res;

	i = 0;
	res = 0;
	while (str[i] != '\0')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res);
}

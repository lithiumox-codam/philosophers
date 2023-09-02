/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/03 14:08:36 by mdekker       #+#    #+#                 */
/*   Updated: 2023/09/02 16:19:28 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philos.h>

int	main(int ac, char **av)
{
	t_data	data;

	data = (t_data){};
	if (ac < 5 || ac > 6)
		return (printf("Error: wrong amount of arguments\n"), 1);
	init(&data, ac, av);
	return (0);
}
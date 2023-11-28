/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/17 23:48:40 by mdekker       #+#    #+#                 */
/*   Updated: 2023/07/18 00:31:05 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(const char *s1, const char *s2)
{
	int x;

	x = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[x] == s2[x] && s1[x] != '\0')
		x++;
	return ((unsigned int)(s1[x] - s2[x]));
}
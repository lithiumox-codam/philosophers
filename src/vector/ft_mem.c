/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_mem.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/03 16:08:20 by mdekker       #+#    #+#                 */
/*   Updated: 2023/09/03 18:26:33 by lithium       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <vector.h>

/**
 * @brief Copies n bytes from src to dst
 *
 * @param dst Address of memory to copy to
 * @param src Address of memory to copy from
 * @param n Amount of bytes to copy
 * @return void* Address of dst
 */
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*destination;
	const char	*source;

	destination = dst;
	source = src;
	if (dst == NULL && src == NULL)
		return (NULL);
	while (n-- > 0)
		*(destination++) = *(source++);
	return (dst);
}

static void	ft_loop(char *dst, char *src, size_t len, size_t dir)
{
	size_t	i;

	i = 0;
	if (dir == 0)
	{
		while (i < len)
		{
			dst[i] = src[i];
			i++;
		}
	}
	else if (dir == 1)
	{
		i = len;
		while (i > 0)
		{
			i--;
			dst[i] = src[i];
		}
	}
}

/**
 * @brief Copies len bytes from src to dst. The two strings may overlap.
 *
 * @param dst Address of memory to copy to
 * @param src Address of memory to copy from
 * @param len Amount of bytes to copy
 * @return void* Address of dst
 */
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*to;
	char	*from;

	to = (char *)dst;
	from = (char *)src;
	if (to < from)
		ft_loop(to, from, len, 0);
	else if (to > from)
		ft_loop(to, from, len, 1);
	return (dst);
}
/**
 * @brief Copies n bytes from src to dst
 *
 * @note The two strings may overlap
 * @param dst Address of memory to copy to
 * @param src Address of memory to copy from
 */
void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*str;

	str = s;
	while (n > 0)
	{
		*str = (unsigned char)c;
		str++;
		n--;
	}
	return (s);
}
/**
 * @brief Sets the first n bytes of the memory area pointed to by s to zero
 * @param s Address of memory to set
 * @param n Amount of bytes to set
 */
void	*ft_bzero(void *s, size_t n)
{
	s = ft_memset(s, 0, n);
	return (s);
}
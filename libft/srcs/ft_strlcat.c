/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:59:06 by antoda-s          #+#    #+#             */
/*   Updated: 2023/10/26 11:49:56 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/// @brief 			Concatenate strings
/// @param dst		Destination string
/// @param src		Source string
/// @param dst_size	Maximum size of the destination string
/// @return			The total length of the string they tried to create
size_t	ft_strlcat(char *dst, const char *src, size_t dst_size)
{
	char		*d;
	const char	*s;
	size_t		dst_free;
	size_t		dst_busy;

	dst_free = dst_size;
	d = dst;
	s = src;
	while (dst_free-- && *d)
		d++;
	dst_busy = d - dst;
	dst_free = dst_size - dst_busy;
	if (dst_free)
	{
		while (*s && dst_free-- > 1)
			*d++ = *s++;
		*d = '\0';
	}
	return (dst_busy + ft_strlen(src));
}

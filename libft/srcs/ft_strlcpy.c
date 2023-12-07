/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:59:06 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/25 15:26:03 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/// @brief 			Copy strings
/// @param dst		Destination string
/// @param src		Source string
/// @param size		Maximum size of the copy
/// @return			The total length of the string they tried to create
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_size;

	src_size = ft_strlen(src);
	if (size == 0)
		return (src_size);
	else if (src_size < size)
	{
		while (*src)
			*dst++ = *src++;
	}
	else
	{
		while (--size)
			*dst++ = *src++;
	}
	*dst = '\0';
	return (src_size);
}

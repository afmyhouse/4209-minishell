/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:28:07 by antoda-s          #+#    #+#             */
/*   Updated: 2023/10/26 11:49:52 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/// @brief 			Fill a byte string with a byte value
/// @param s		Pointer to the block of memory to fill
/// @param c		Byte to fill the memory area with
/// @param n		Number of bytes to be set to the value
/// @return	void	Pointer to the memory area s
void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p_s;

	p_s = (unsigned char *)s;
	while (n--)
		*p_s++ = (unsigned char)c;
	return (s);
}

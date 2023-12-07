/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 22:50:17 by antoda-s          #+#    #+#             */
/*   Updated: 2023/10/26 11:49:52 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/// @brief 		Moves n bytes from memory area src to memory area dest.
/// @param dest	Pointer to destination memory area
/// @param src	Pointer to source memory area
/// @param n	Number of bytes to move
/// @return		Pointer to destination
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*p_dest;
	unsigned char	*p_src;

	p_dest = (unsigned char *)dest;
	p_src = (unsigned char *)src;
	if (n != 0 && p_dest != p_src)
	{
		if (p_dest < p_src)
		{
			while (n--)
				*p_dest++ = *p_src++;
		}
		else if (p_dest > p_src)
		{
			p_dest = (unsigned char *)dest + (n -1);
			p_src = (unsigned char *)src + (n -1);
			while (n--)
				*p_dest-- = *p_src--;
		}
	}
	return (dest);
}

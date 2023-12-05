/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 00:49:13 by antoda-s          #+#    #+#             */
/*   Updated: 2023/10/26 11:49:50 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/// @brief 		Compares byte string s1 against byte string s2.
/// @param s1	Pointer to memory area 1
/// @param s2	Pointer to memory area 2
/// @param n	Number of bytes to compare
/// @return		An integer less than, equal to, or greater than zero if the
///				first n bytes of s1 is found, respectively, to be less than,
///				to match, or be greater than the first n bytes of s2.
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*p_str1;
	unsigned char	*p_str2;

	p_str1 = (unsigned char *)s1;
	p_str2 = (unsigned char *)s2;
	while (n--)
	{
		if (*p_str1++ != *p_str2++)
			return (p_str1[-1] - p_str2[-1]);
	}
	return (0);
}

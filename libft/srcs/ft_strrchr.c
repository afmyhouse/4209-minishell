/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 21:24:38 by antoda-s          #+#    #+#             */
/*   Updated: 2023/10/26 11:49:57 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/// @brief 		Locates the last occurrence of char `c` in the string `s`
/// @param s	String to search
/// @param c	Character to search for
/// @return		Pointer to the located character, or NULL if not found
char	*ft_strrchr(const char *s, int c)
{
	unsigned char	*p_s;

	p_s = (unsigned char *)s;
	while (*p_s)
		p_s++;
	while (p_s >= (unsigned char *)s && *p_s != (unsigned char)c)
		p_s--;
	if (*p_s == (unsigned char)c)
		return ((char *)p_s);
	return (NULL);
}

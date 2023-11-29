/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:27:02 by antoda-s          #+#    #+#             */
/*   Updated: 2023/10/26 11:49:55 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/// @brief 			Locates the first occurrence of char `c` in the string `s`
/// @param s		String to search
/// @param c		Character to search for
/// @return			Pointer to the located character, or NULL if not found
char	*ft_strchr(const char *s, int c)
{
	if (!s || !*s || !c)
		return (NULL);
	while (*s)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

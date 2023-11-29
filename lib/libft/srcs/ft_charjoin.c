/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 00:28:11 by antoda-s          #+#    #+#             */
/*   Updated: 2023/10/26 11:53:06 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/// @brief		Allocates (with malloc(3)) and returns a new string, which is
///				the result of the concatenation of ’s1’ and the char ’c’.
/// @param s1	The prefix string.
/// @param c	The char to concatenate.
/// @return		The new string or NULL if the allocation fails.
char	*ft_charjoin(char const *s1, char const c)
{
	size_t	len;
	char	*dest;

	if (!s1 && !c)
		return (NULL);
	if (s1)
		len = ft_strlen(s1) + sizeof(c) + 1;
	else
		len = sizeof(c) + 1;
	dest = ft_calloc(len, sizeof(char));
	if (!dest)
		return (NULL);
	if (s1)
		while (*s1)
			*dest++ = *s1++;
	*dest++ = c;
	*dest = '\0';
	dest -= (len - 1);
	return (dest);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:27:02 by antoda-s          #+#    #+#             */
/*   Updated: 2023/12/04 21:23:04 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/// @brief 			Locates the first occurrence of the null-terminated string
/// @param big		String where to search occurences of `little` string
/// @param little	Substring to search for
/// @param len		Number of bytes to search
/// @return			Pointer to the located character, or NULL if not found
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*phs;
	size_t	len_big;

	len_big = ft_strlen(big);
	phs = (char *)big;
	if (!*little)
		return (phs);
	if (len == 0 || !*phs)
		return (NULL);
	if (len > ft_strlen(big))
		len = ft_strlen(big);
	while (*phs && (size_t)(phs - big + len_big) >= len)
	{
		if (!ft_strncmp(phs, little, len_big))
			return (phs);
		phs++;
	}
	return (NULL);
}

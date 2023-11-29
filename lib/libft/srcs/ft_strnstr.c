/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:27:02 by antoda-s          #+#    #+#             */
/*   Updated: 2023/10/26 11:49:57 by antoda-s         ###   ########.fr       */
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
	size_t	lns;

	lns = ft_strlen(little);
	phs = (char *)big;
	if (!*little)
		return (phs);
	if (len == 0 || !*phs)
		return (NULL);
	if (len > ft_strlen(big))
		len = ft_strlen(big);
	while (*phs && (size_t)(phs - big + lns) <= len)
	{
		if (!ft_strncmp(phs, little, lns))
			return (phs);
		phs++;
	}
	return (NULL);
}

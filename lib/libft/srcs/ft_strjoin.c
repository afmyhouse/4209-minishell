/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 00:28:11 by antoda-s          #+#    #+#             */
/*   Updated: 2023/10/26 11:49:56 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/// @brief 			Concatenate strings NO SEPARATOR
/// @param s1		FIRST string
/// @param s2		SECOND string
/// @return			The new string
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*dst;
	char	*ret;

	if (!s1 || !*s1)
		len = ft_strlen(s2);
	else
		len = ft_strlen(s1) + ft_strlen(s2);
	dst = ft_calloc(len + 1, sizeof(char));
	if (!dst)
		return (NULL);
	ret = dst;
	if (s1)
	{
		while (*s1)
			*dst++ = *s1++;
	}
	while (*s2)
		*dst++ = *s2++;
	return (ret);
}

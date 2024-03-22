/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:27:02 by antoda-s          #+#    #+#             */
/*   Updated: 2024/03/22 20:10:35 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/// @brief 			Locates the first occurrence of char `c` in the string `s`
/// @param s		String to search
/// @param c		Character to search for
/// @return			Pointer to the located character, or NULL if not found
char	*ft_strchr(const char *s, int c)
{
	if (s && *s && c)
	{
		while (*s)
		{
			if (*s == (unsigned char)c)
				return ((char *)s);
			s++;
		}
	}
	return (NULL);
}

/// @brief 			Locates the first occurrence of char `c` in the string `s`
/// @param s		String to search
/// @param c		Character to search for
/// @return			Pointer to the located character, or NULL if not found
int	ft_strchr_i(const char *s, int c)
{
	int	i;

	if (s && *s && c)
	{
		i = -1;
		while (s[++i])
			if (s[i] == (unsigned char)c)
				return (i);
	}
	return (-1);
}

/// @brief 		Detects the occurrence of char from set in string s
/// @param str	string to process
/// @param set	set of chars
/// @return		char found or 0
char	ft_strset(const char *s, const char *set)
{
	if (!s || !*s || !set)
		return ('\0');
	while (*set && !ft_strchr(s, *set))
		set++;
	return (*set);
}

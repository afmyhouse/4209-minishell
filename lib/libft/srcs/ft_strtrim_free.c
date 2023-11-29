/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 21:34:19 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/01 21:47:41 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/// @brief 			Allocates (with malloc(3)) and returns a copy of
/// @param line		The string to be trimmed.
/// @param set		The reference set of characters to trim.
/// @return			The trimmed string or NULL if the allocation fails.
char	*ft_strtrim_free(char *line, char const *set)
{
	char	*trim;

	trim = ft_strtrim(line, set);
	free(line);
	return (trim);
}

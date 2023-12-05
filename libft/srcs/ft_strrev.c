/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:21:20 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/18 12:38:40 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/// @brief 		reverts the order of an array contents
/// @param str	the array to revert
/// @param j	reversion stop index: 0 reverts all, otherwise reverts until
///				the specified index (index excluded, so j = 1 reverts until
///				the first element)
/// @return		the reverted array
char	*ft_strrev(char *str, int j)
{
	char	temp;
	int		i;

	i = 0;
	if (!j)
		j = ft_strlen(str) - 1;
	if ((j - i) <= 0)
		return (str);
	while (i <= j)
	{
		temp = str[i];
		str[i++] = str[j];
		str[j--] = temp;
	}
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 22:45:42 by antoda-s          #+#    #+#             */
/*   Updated: 2023/10/26 11:53:07 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/// @brief 		Checks is an alphabetic upper case character.
/// @param c	Character to check
/// @return		1 if c is alphabetic, 0 otherwise
static int	ft_isupper(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}

/// @brief 		Checks is an alphabetic lower case character.
/// @param c	Character to check
/// @return		1 if c is alphabetic, 0 otherwise
static int	ft_islower(int c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	return (0);
}

/// @brief 		Checks for an alphabetic character.
/// @param c	Character to check
/// @return		1 if c is alphabetic, 0 otherwise
int	ft_isalpha(int c)
{
	if (ft_islower(c) || ft_isupper(c))
		return (1);
	return (0);
}

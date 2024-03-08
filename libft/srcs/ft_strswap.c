/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strswap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 21:39:52 by antoda-s          #+#    #+#             */
/*   Updated: 2024/02/25 21:40:50 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/// @brief 			Swaps two strings
/// @param s1 		First string
/// @param s2 		Second string
void	ft_strswap(char **s1, char **s2)
{
	char	*tmp;

	if (!s1 || !s2)
		return ;
	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

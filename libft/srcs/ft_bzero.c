/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:12:42 by antoda-s          #+#    #+#             */
/*   Updated: 2024/04/03 23:02:37 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/// @see		ft_memset
/// @brief 		Fills a byte string with zeros.
/// @param s	Pointer to string
/// @param n	Number of bytes to fill
void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
	return ;
}

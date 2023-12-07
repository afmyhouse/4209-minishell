/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoc_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:38:13 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/17 17:38:40 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/// @brief 			convert int number <n> to a printable equivalente char
/// @param n		int <n> to convert to printable char
/// @param radix	base of numeration of str n
/// @return			c char converted
char	ft_itoc_base(const int n, char base)
{
	if (n >= 0 && n <= 9)
		return ((char)n + '0');
	else if (n > 9 && n < 16)
		return ((char)((n - 10) + (base - 23)));
	else
		return ((char)n);
}

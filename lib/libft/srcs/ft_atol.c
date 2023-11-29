/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 23:53:58 by antoda-s          #+#    #+#             */
/*   Updated: 2023/10/26 11:53:03 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/// @brief 		Converts the initial portion of the string pointed to by nptr
///				to long int
/// @param nptr	The string to convert
/// @return		The converted long int
long	ft_atol(const char *nptr)
{
	int			signal;
	long int	number;

	signal = 1;
	number = 0;
	while (ft_isspace(*nptr))
		nptr++;
	if (ft_issign(*nptr))
		signal *= ft_issign(*nptr++);
	while (ft_isdigit(*nptr))
		number = number * 10 + (*nptr++ - '0');
	return (number * signal);
}

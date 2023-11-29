/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:54:38 by antoda-s          #+#    #+#             */
/*   Updated: 2023/10/26 11:51:45 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/// @brief 		Converts the initial portion of the string pointed to by nptr
/// @param nptr	Pointer to string
/// @return		The converted integer
int	ft_atoi(const char *nptr)
{
	int	signal;
	int	number;

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

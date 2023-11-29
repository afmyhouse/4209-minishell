/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 13:05:46 by antoda-s          #+#    #+#             */
/*   Updated: 2023/10/26 11:53:08 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/// @brief 		Converts the integer n to a string
/// @param n	The integer to convert
/// @return		The string representation of the integer
char	*ft_itoa(int n)
{
	char		*res;
	int			len;
	long int	ln;

	ln = n;
	len = 0;
	if (n <= 0)
		len++;
	while (n && len++ >= 0)
		n /= 10;
	res = (char *)malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	res[len] = '\0';
	n = ln;
	if (ln < 0)
		ln = -ln;
	while (--len >= 0)
	{
		res[len] = ln % 10 + 48;
		ln /= 10;
	}
	if (n < 0)
		res[0] = '-';
	return (res);
}

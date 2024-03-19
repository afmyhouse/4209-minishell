/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoc_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:38:13 by antoda-s          #+#    #+#             */
/*   Updated: 2024/03/19 14:28:10 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_basei(char base)
{
	if (base == 'd')
		return (10);
	else if (base == 'x' || base == 'X')
		return (16);
	else if (base == 'o')
		return (8);
	else if (base == 'b')
		return (2);
	else
		return (0);
}

char	*ft_itoa_base_str(const long int n, char base)
{
	int			basei;
	char		*res;
	int			len;
	long int	ln;

	ln = n;
	len = 0;
	basei = ft_basei(base);
	if ((ln <= 0 && basei == 10) || basei == 8 || basei == 2)
		len++;
	else if (basei == 16)
		len += 2;
	while (ln && len++ >= 0)
		ln /= basei;
	res = (char *)malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	res[len] = '\0';
	while (len-- > 0)
		res[len] = '0';
	return (res);
}

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

/// @brief 		Converts the integer n to a string
/// @param n	The integer to convert
///
/// @return		The string representation of the integer
char	*ft_itoa_base(const long int n, char base)
{
	int			basei;
	char		*res;
	int			len;
	long int	ln;

	ln = n;
	len = 0;
	basei = ft_basei(base);
	res = ft_itoa_base_str(n, base);
	len = ft_strlen(res);
	while (--len >= 0)
	{
		res[len] = ft_itoc_base(ln % basei, base);
		ln /= basei;
	}
	if (n < 0 && basei == 10)
		res[0] = '-';
	else if (basei == 16)
	{
		res[0] = '0';
		res[1] = base;
	}
	else if (basei == 8 || basei == 2)
		res[0] = base;
	return (res);
}

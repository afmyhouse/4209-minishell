/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 20:53:41 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/04 11:31:15 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*ft_decitoa(float n, int p)
{
	char	*res;
	int		ln;
	int		i;

	i = -1;
	res = (char *)malloc((p + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (++i < p)
	{
		n *= 10;
		ln = (int)n;
		n = n - ln;
		res[i] = ln % 10 + 48;
	}
	res[i] = '\0';
	return (res);
}

/// @brief 		Converts a float to a string
/// @param f	The float to be converted
/// @return		The string representation of the float
char	*ft_ftoa(float f, int p)
{
	char	*part;
	char	*tmp;
	char	*res;
	int		ipart;
	float	fpart;

	ipart = (int)f;
	fpart = (float)((f - ipart));
	if (f < 0)
		fpart *= -1;
	part = ft_itoa(ipart);
	if (ipart == 0 && f < 0)
	{
		tmp = ft_strjoin("-", part);
		free(part);
		part = tmp;
	}
	tmp = ft_strjoin(part, ".");
	free(part);
	part = ft_decitoa(fpart, p);
	res = ft_strjoin(tmp, part);
	free(tmp);
	free(part);
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 14:13:52 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/17 17:41:53 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/**********ft_pf_tools1.c**********/
/// @brief 		negative SIGNAL flag if "arg" passed by address is negative
/// @param f 	struct where to store the flag SIGNAL
/// @param arg 	number to eval signal
void	ft_pf_fwp_u(t_printf *f, void *arg)
{
	long double	ld_arg;
	int			li_arg;

	if ((*f).at == 'i' || (*f).at == 'd')
	{
		li_arg = *(int *)arg;
		if (li_arg < 0)
		{
			li_arg *= -1;
			(*f).f_stype = '-';
		}
		*(int *)arg = li_arg;
	}
	else if ((*f).at == 'f' || (*f).at == 'a' || (*f).at == 'A' || \
		(*f).at == 'e' || (*f).at == 'E')
	{
		ld_arg = *(long double *)arg;
		if (ld_arg < 0)
		{
			ld_arg *= -1;
			(*f).f_stype = '-';
		}
		*(long double *)arg = ld_arg;
	}
}

/// @brief 		reverts the order of an array contents
/// @param str	the array to revert
/// @param j	length of the array pointed by str
/// @return		the reverted array
// char	*ft_pf_tools_strrev(char *str, int j)
// {
// 	char	temp;
// 	int		i;

// 	i = 0;
// 	j = ft_strlen(str) - 1;
// 	if ((j - i) <= 0)
// 		return (str);
// 	while (i <= j)
// 	{
// 		temp = str[i];
// 		str[i++] = str[j];
// 		str[j--] = temp;
// 	}
// 	return (str);
// }

/// @brief 		using the char specifier determines de radix of the arg
/// @param base the specifier of the number type
/// @return 	the radix number :2(b), 8(o), 16(x, X)), 10(else)
char	ft_pf_base2radix(char base)
{
	if (base == 'b')
		return (2);
	else if (base == 'o')
		return (8);
	else if (base == 'x' || base == 'X' || base == 'a' || \
		base == 'A' || base == 'p')
		return (16);
	else
		return (10);
}

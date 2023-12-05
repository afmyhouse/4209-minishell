/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 22:15:37 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/07 09:44:58 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	ft_intcmp(int a, int b)
{
	if (a == b)
		return (0);
	else if (a < b)
		return (-1);
	return (1);
}

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

unsigned int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

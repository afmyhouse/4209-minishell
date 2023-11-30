/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   99error.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 22:37:00 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/30 20:31:06 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/// @brief 			Shows error and program sourcing it
/// @param msg		Message to show
/// @param system	Shows system error if true
/// @return			SUCCESS
int	return_error(const char *msg, int system)
{
	ft_putstr_fd("Minishell: ", 2);
	if (system)
		perror(msg);
	else
		ft_putendl_fd(msg, 2);
	return (1);
}

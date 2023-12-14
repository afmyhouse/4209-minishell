/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   99ms_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 22:37:00 by antoda-s          #+#    #+#             */
/*   Updated: 2023/12/13 23:12:34 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/// @brief 			Shows error and program sourcing it
/// @param msg		Message to show
/// @param system	Shows system error if true
/// @return			SUCCESS
int	return_error(const char *msg, int system)
{
	show_func(__func__, MY_START);
	ft_putstr_fd("Minishell: ", 2);
	if (system)
		perror(msg);
	else
		ft_putendl_fd(msg, 2);
	show_func(__func__, SUCCESS);
	return (1);
}

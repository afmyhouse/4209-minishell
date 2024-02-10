/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   910_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 22:37:00 by antoda-s          #+#    #+#             */
/*   Updated: 2024/02/10 00:15:32 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief 			Shows error and program sourcing it
/// @param msg		Message to show
/// @param system	Shows system error if true
/// @return			SUCCESS
int	export_error(const char *msg, int system)
{
	//show_func(__func__, MY_START, NULL);

	ft_putstr_fd("Minishell: export: '", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	errno = system;
	//show_func(__func__, SUCCESS, NULL);
	return (system);
}

/// @brief 			Shows error and program sourcing it
/// @param msg		Message to show
/// @param system	Shows system error if true
/// @return			SUCCESS
int	return_error(const char *msg, int errms, int errbash)
{
	//show_func(__func__, MY_START, NULL);
	ft_putstr_fd("Minishell: ", 2);
	g_exit_status = errms;
	if (errbash)
		perror(msg);
	else
		ft_putendl_fd(msg, 2);
	//show_func(__func__, SUCCESS, NULL);
	return (1);
}

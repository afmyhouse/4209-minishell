/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   910_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 22:37:00 by antoda-s          #+#    #+#             */
/*   Updated: 2024/03/22 21:53:07 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief 			Shows error and program sourcing it
/// @param msg		Message to show
/// @param system	Shows system error if true
/// @return			SUCCESS
int	export_error(const char *msg, int errms)
{
	char	*msgr;
	char	*msgt;
	int		status;

	msgt = ft_strjoin(msg, "': not a valid identifier");
	msgr = ft_strjoin("export: `", msgt);
	free(msgt);
	status = return_error(msgr, errms, 0);
	free(msgr);
	return (status);
}

/// @brief 			Shows error and program sourcing it
/// @param msg		Message to show
/// @param system	Shows system error if true
/// @return			SUCCESS
int	flags_error(const char *cmd, char *flag, int errms)
{
	char	*msgr;
	char	*msgt;
	int		status;

	msgt = ft_strjoin(flag, "': flags and options not allowed");
	msgr = ft_strjoin(": '", msgt);
	free(msgt);
	msgt = ft_strjoin(cmd, msgr);
	status = return_error(msgt, errms, 0);
	free(msgt);
	free(msgr);
	return (status);
}

/// @brief 			Shows error and program sourcing it
/// @param msg		Message to show
/// @param system	Shows system error if true
/// @return			SUCCESS
int	return_error(const char *msg, int errms, int errbash)
{
	if (!errbash)
		ft_putstr_fd("minishell: ", 2);
	g_exit_status = errms;
	if (errbash)
	{
		if (!errms)
			g_exit_status = errno;
		perror(msg);
	}
	else
		ft_putendl_fd(msg, 2);
	return (1);
}

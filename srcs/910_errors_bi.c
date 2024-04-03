/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   910_errors_bi.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 22:37:00 by antoda-s          #+#    #+#             */
/*   Updated: 2024/04/04 00:52:12 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief 			Shows error and program sourcing it
/// @param msg		Message to show
/// @param system	Shows system error if true
/// @return			SUCCESS
int	error_export(const char *msg, int errms)
{
	show_func(__func__, FSTART, NULL);
	char	*msgr;
	char	*msgt;
	int		status;

	msgt = ft_strjoin(msg, "': not a valid identifier");
	msgr = ft_strjoin("export: `", msgt);
	free(msgt);
	status = error_return(msgr, errms, 0);
	free(msgr);
	return (status);
}

/// @brief 			Shows error and program sourcing it
/// @param msg		Message to show
/// @param system	Shows system error if true
/// @return			SUCCESS
int	error_exit_args(const char *msg, int system)
{
	show_func(__func__, FSTART, NULL);
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(msg, 2);
	errno = system;
	return (system);
}

/// @brief 			Shows error and program sourcing it
/// @param msg		Message to show
/// @param system	Shows system error if true
/// @return			SUCCESS
int	error_bi_flags(const char *cmd, char *flag, int errms)
{
	show_func(__func__, FSTART, NULL);
	char	*msgr;
	char	*msgt;
	int		status;

	msgt = ft_strjoin(flag, "': flags and options not allowed");
	msgr = ft_strjoin(": '", msgt);
	free(msgt);
	msgt = ft_strjoin(cmd, msgr);
	status = error_return(msgt, errms, 0);
	free(msgt);
	free(msgr);
	return (status);
}

/// @brief 			Shows error and program sourcing it
/// @param msg		Message to show
/// @param system	Shows system error if true
/// @return			SUCCESS
int	error_return(const char *msg, int errms, int errbash)
{
	show_func(__func__, FSTART, NULL);
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

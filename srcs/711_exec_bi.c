/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   711_exec_bi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:25:54 by antoda-s          #+#    #+#             */
/*   Updated: 2024/03/19 00:04:03 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief 			Executes a builtin command according to its id
/// @param id 		Builtin command id
/// @param s 		Script contents and parameters including redirect info
/// @param i 		Index of the command to execute
/// @return 		SUCCESS or ERROR
int	exec_bi(int id, t_script *s, int i)
{
	if (id == CMD_EQ)
		g_exit_status = bi_equal(s, i);
	else if (id == CMD_ECHO)
		g_exit_status = bi_echo(s, i);
	else if (id == CMD_CD)
		g_exit_status = bi_cd(s, i);
	else if (id == CMD_PWD)
		g_exit_status = bi_pwd(s, i);
	else if (id == CMD_EXPORT)
		g_exit_status = bi_export(s, i);
	else if (id == CMD_UNSET)
		g_exit_status = bi_unset(s, i);
	else if (id == CMD_ENV)
		g_exit_status = bi_env(s, i);
	else if (id == CMD_EXIT)
		return (bi_exit(s, i));
	return (SUCCESS);
}

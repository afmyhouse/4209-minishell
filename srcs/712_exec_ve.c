/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   712_exec_ve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:25:54 by antoda-s          #+#    #+#             */
/*   Updated: 2024/03/13 23:26:37 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_ve_abs(char **cmd, char **env)
{
	show_func(__func__, MY_START, NULL);
	if (execve(*cmd, cmd, env) == -1)
		g_exit_status = errno;
}

void	exec_ve_path(char **path, char **cmd, char **env)
{
	show_func(__func__, MY_START, NULL);
	char	*tmp;
	int		i;
	int		ret;

	tmp = ft_strdup(*cmd);
	i = 0;
	ret = -1;
	while (ret == -1 && path[i])
	{
		ft_free(tmp);
		tmp = ft_strjoin(path[i], *cmd);
		if (!tmp)
			break ;
		ret = execve(tmp, cmd, env);
		i++;
	}
	// if (tmp)
	ft_free(tmp);
}

/// @brief 			Executes a command using the absolute path or the PATH
/// @param path 	Commands execution path
/// @param cmd 		Command to execute
/// @param env 		Environment variables
void	exec_ve(char **path, char **cmd, char **env)
{
	show_func(__func__, MY_START, NULL);
	if (*cmd[0] == '.' || *cmd[0] == '/')
	{
		exec_ve_abs(cmd, env);
		return ;
	}
	if (path)
		exec_ve_path(path, cmd, env);
	else
		return ;
}

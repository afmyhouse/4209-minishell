/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   731_exec_go.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:11:17 by antoda-s          #+#    #+#             */
/*   Updated: 2024/03/11 01:40:21 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_ve_err_127(t_script *s, char **path, int i)
{
	char	*msg;

	msg = ft_strjoin("Minishell: ", s->cmds[i].argv[0]);
	return_error(msg, 127, 1);
	free (msg);
	free_cmds_path(s, path);
	exit(127);
}

/// @brief 			Executes the command (execeve or bi )
/// @param s 		Script contents and parameters including redirect info
/// @param path 	Commands execution path
/// @param id 		Command type
/// @param i 		Index of the command to execute
void	exec_go(t_script *s, char **path, int id, int i)
{
	show_func(__func__, MY_START, NULL);
	struct stat	buf;

	if (id == CMD_EX)
	{
		if (!s->cmds[i].argv[0][0])
			return ;
		stat(s->cmds[i].argv[0], &buf);
		exec_ve(path, s->cmds[i].argv, s->envp);
		if (S_ISDIR(buf.st_mode))
			errno = EISDIR;
		if (ft_strchr(s->cmds[i].argv[0], '/') != NULL)
			exec_ve_err_127(s, path, i);
		else if (errno != ENOENT)
			perror(s->cmds[i].argv[0]);
		else
		{
			ft_putstr_fd(s->cmds[i].argv[0], 2);
			ft_putendl_fd(": command not found", 2);
		}
		free_cmds_path(s, path);
		exit(127);
	}
	else
		exec_bi(id, s, i);
}

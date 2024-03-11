/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   731_exec_go.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:11:17 by antoda-s          #+#    #+#             */
/*   Updated: 2024/03/10 23:45:11 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief 			Executes the command (execeve or bi )
/// @param s 		Script contents and parameters including redirect info
/// @param path 	Commands execution path
/// @param id 		Command type
/// @param i 		Index of the command to execute
void	exec_go(t_script *s, char **path, int id, int i)
{
	show_func(__func__, MY_START, NULL);
	char		*tmp;
	char		*msg;
	struct stat	buf;

	if (id == CMD_EX)
	{
		tmp = s->cmds[i].argv[0];
		msg = ft_strjoin("Minishell: ", s->cmds[i].argv[0]);
		if (!tmp[0])
			return ;
		stat(tmp, &buf);
		exec_ve(path, s->cmds[i].argv, s->envp);
		if (S_ISDIR(buf.st_mode))
			errno = EISDIR;
		if (ft_strchr(s->cmds[i].argv[0], '/') != NULL)
		{
			free_cmds_path(s, path);
			return_error(msg, 127, 1);
			free (msg);
			exit (127);
		}
		ft_putstr_fd("Minishell: ", 2);
		if (errno != ENOENT)
			perror(tmp);
		else
		{
			ft_putstr_fd(tmp, 2);
			ft_putendl_fd(": command not found", 2);
		}
		free_cmds_path(s, path);
		exit(127);
	}
	else
		exec_bi(id, s, i);
}

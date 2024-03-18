/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   731_exec_go.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:11:17 by antoda-s          #+#    #+#             */
/*   Updated: 2024/03/13 23:55:25 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_ve_err(t_script *s, char **path, int i)
{
	char	*msg;

	(void) path;
	msg = ft_strjoin("Minishell: ", s->cmds[i].argv[0]);
	return_error(msg, 127, 1);
	ft_free(msg);
	free_exit(s, 0);
	if (errno == 21)
		exit (126);
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

	(void) path;
	memset(&buf, 0, sizeof(struct stat));
	if (id == CMD_EX)
	{
		if (!s->cmds[i].argv[0][0])
			return ;
		stat(s->cmds[i].argv[0], &buf);
		exec_ve(s->path, s->cmds[i].argv, s->envp);
		if (S_ISDIR(buf.st_mode) && s->cmds[i].argv[0][0] == '.')
			errno = EISDIR;
		if (ft_strchr(s->cmds[i].argv[0], '/') != NULL
			|| (errno == ENOENT && !s->path))
			exec_ve_err(s, s->path, i);
		else if (errno != ENOENT)
			perror(s->cmds[i].argv[0]);
		else
			ft_printf("%s: command not found\n", s->cmds[i].argv[0]);
		free_exit(s, 0);
		exit(127);
	}
	else
		exec_bi(id, s, i);
}

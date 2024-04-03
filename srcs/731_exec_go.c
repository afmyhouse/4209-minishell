/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   731_exec_go.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:11:17 by antoda-s          #+#    #+#             */
/*   Updated: 2024/04/04 00:51:21 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_ve_err(t_script *s, int i)
{
	show_func(__func__, FSTART, NULL);
	char	*msg;

	msg = ft_strjoin("minishell: ", s->cmds[i].argv[0]);
	error_return(msg, 127, 1);
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
void	exec_go(t_script *s, int id, int i)
{
	show_func(__func__, FSTART, NULL);
	struct stat	buf;

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
			exec_ve_err(s, i);
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

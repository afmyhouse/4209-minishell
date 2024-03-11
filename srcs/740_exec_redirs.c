/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   740_exec_redirs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:07:19 by antoda-s          #+#    #+#             */
/*   Updated: 2024/03/10 23:45:22 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief 		After fork, child process calls this fucntion prepare redirect
///				from a file.
/// 			The input of next command will be a file isntead of a STDIN
/// 			If the  input is from a here doc instead, it will call
/// 			the heredoc function
/// @param s 	Script contents and parameters including redirect info
/// @param i 	Index of the command to be executed
/// @param path Commands execution path
void	in_redir(t_script *s, int i, char **path)
{
	show_func(__func__, MY_START, NULL);
	int	fdin;

	if (s->cmds[i].in.flag >= 0)
	{
		fdin = open(s->cmds[i].in.name, s->cmds[i].in.flag);
		if (fdin == -1)
			exit_forks(s->cmds[i].in.name, 1, s, path);
		else if (fdin != STDIN_FILENO && dup2(fdin, STDIN_FILENO) == -1)
		{
			close(fdin);
			exit_forks("Error: dup2 failed", 1, s, path);
		}
	}
	else
		heredoc(s, i, path);
}

/// @brief 		After fork this fucntion is called to prepare redirect to a file
///				A previous output to STDOUT will be redirected to the file
/// @param s 	Script contents and parameters including redirect info
/// @param i 	Index of the command to be executed
/// @param path Commands execution path
void	out_redir(t_script *s, int i, char **path)
{
	show_func(__func__, MY_START, NULL);
	int	fdout;

	fdout = open(s->cmds[i].out.name, s->cmds[i].out.flag, 0644);
	if (fdout == -1)
		exit_forks(s->cmds[i].out.name, 1, s, path);
	else if (fdout != STDOUT_FILENO && dup2(fdout, STDOUT_FILENO) == -1)
	{
		close(fdout);
		exit_forks("Error: dup2 failed", 1, s, path);
	}
	close(fdout);
}

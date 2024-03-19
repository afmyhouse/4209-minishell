/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   730_exec_childs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:11:17 by antoda-s          #+#    #+#             */
/*   Updated: 2024/03/19 14:02:22 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief 			Executes the first command in a pipe
/// @param s 		Script contents and parameters including redirect info
/// @param path 	Commands execution path
/// @param pipeout	Pointer to the pipe to output result
void	ex_child_1(t_script *s, int *pipeout)
{
	if (s->cmds[0].in.name)
		in_redir(s, 0);
	if (s->cmds[0].out.name)
		out_redir(s, 0);
	else if (pipeout)
	{
		if (pipe_std_setter(pipeout, STDOUT_FILENO) == -1)
		{
			pipe_closer(pipeout, NULL);
			exit_forks("pipe setter failed to set stdou/stdin", 1, s);
		}
		pipe_closer(pipeout, NULL);
	}
	if (s->cmds[0].argv[0])
		exec_go(s, exec_type(s->cmds[0].argv[0]), 0);
	free_exit(s, 0);
	exit(SUCCESS);
}

/// @brief 			Executes the command in the middle of a pipe
/// @param s 		Script contents and parameters including redirect info
/// @param path 	Commands execution path
/// @param pipes 	Pointer to the pipes, IN and OUT
/// @param i 		Index of the command to execute
void	ex_child_i(t_script *s, int **pipes, int i)
{
	if (s->cmds[i].in.name)
		in_redir(s, i);
	else if (pipe_std_setter(pipes[0], STDIN_FILENO) == -1)
	{
		pipe_closer(pipes[0], pipes[1]);
		exit_forks("pipe setter failed to set stdou/stdin", 1, s);
	}
	if (s->cmds[i].out.name)
		out_redir(s, i);
	else if (pipe_std_setter(pipes[1], STDOUT_FILENO) == -1)
	{
		pipe_closer(pipes[0], pipes[1]);
		exit_forks("pipe setter failed to set stdou/stdin", 1, s);
	}
	pipe_closer(pipes[0], pipes[1]);
	if (s->cmds[i].argv[0])
		exec_go(s, exec_type(s->cmds[i].argv[0]), i);
	free (pipes);
	free_exit(s, 0);
	exit(SUCCESS);
}

/// @brief 			Executes the last command in a pipe
/// @param s 		Script contents and parameters including redirect info
/// @param path 	Commands execution path
/// @param pipein 	Pointer to the pipe
/// @param i
void	ex_child_n(t_script *s, int *pipein, int i)
{
	if (s->cmds[i].in.name)
		in_redir(s, i);
	else if (pipe_std_setter(pipein, STDIN_FILENO) == -1)
	{
		pipe_closer(pipein, NULL);
		exit_forks("pipe setter failed to set stdou/stdin", 1, s);
	}
	if (s->cmds[i].out.name)
		out_redir(s, i);
	pipe_closer(pipein, NULL);
	if (s->cmds[i].argv[0])
		exec_go(s, exec_type(s->cmds[i].argv[0]), i);
	free_exit(s, 0);
	exit(0);
}

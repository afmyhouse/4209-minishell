/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 16:28:30 by mdeclerf          #+#    #+#             */
/*   Updated: 2021/10/07 17:25:02 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
in_redir(t_script *s, int i, char **path_env) :
	This function is called in every child function in case we have to 
	redirect the input.
	It also calls heredoc (heredoc.c) in case the input comes from a heredoc.
*/
void	in_redir(t_script *s, int i, char **path_env)
{
	int	fdin;

	if (s->commands[i].in.flag >= 0)
	{
		fdin = open(s->commands[i].in.name, s->commands[i].in.flag);
		if (fdin == -1)
		{
			return_error(s->commands[i].in.name, 1);
			free_cmds_path(s, path_env);
			exit(1);
		}
		else if (fdin != STDIN_FILENO)
		{
			if (dup2(fdin, STDIN_FILENO) == -1)
			{
				ft_putendl_fd("Minishell: Error: dup2 failed", 2);
				close(fdin);
				free_cmds_path(s, path_env);
				exit(1);
			}
		}
	}
	else
		heredoc(s, i, path_env);
}

/*
out_redir(t_script *s, int i, char **path_env) :
	This function is called in every child function in case we have to 
	redirect the output.
*/
void	out_redir(t_script *s, int i, char **path_env)
{
	int	fdout;

	fdout = open(s->commands[i].out.name, s->commands[i].out.flag, 0644);
	if (fdout == -1)
	{
		return_error(s->commands[i].out.name, 1);
		free_cmds_path(s, path_env);
		exit(1);
	}
	else if (fdout != STDOUT_FILENO)
	{
		if (dup2(fdout, STDOUT_FILENO) == -1)
		{
			ft_putendl_fd("Minishell: Error: dup2 failed", 2);
			close(fdout);
			free_cmds_path(s, path_env);
			exit(1);
		}
	}
	close(fdout);
}

void	close_pipes(int *pipe1, int *pipe2)
{
	close(pipe1[0]);
	close(pipe1[1]);
	if (pipe2)
	{
		close(pipe2[0]);
		close(pipe2[1]);
	}
}

/*
pipe_dup(int *pipe, int mod, int std) :
	This function is called every time we have to dup. It takes the pipe,
	the extremity we have to dup and the STDIN/STDOUT we have to
	replace as parameters.
*/
int	pipe_dup(int *pipe, int mod, int std)
{
	if (pipe[mod] != std)
	{
		if (dup2(pipe[mod], std) == -1)
		{
			write(2, "Minishell: Error: dup2 failed\n", 19);
			return (1);
		}
	}
	return (0);
}

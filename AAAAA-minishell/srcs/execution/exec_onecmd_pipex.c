/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_onecmd_pipex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 16:28:45 by mdeclerf          #+#    #+#             */
/*   Updated: 2021/10/07 17:25:20 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
one_cmd_exec(t_script *script, char **path_env) :
	This function is called by one_cmd if the cmd is not a builtin.
	It forks and calls first_child which will execute normally like if
	there multiple cmds, but we send it NULL meaning it won't have
	to redirect the output to a pipe.
*/
static int	one_cmd_exec(t_script *script, char **path_env)
{
	int	pid;

	if (script->commands[0].in.flag == -1)
		signal(SIGQUIT, SIG_IGN);
	else
		signal(SIGQUIT, sig_handler_fork);
	signal(SIGINT, sig_handler_fork);
	pid = fork();
	if (pid == -1)
		return (fork_error(path_env));
	if (pid == 0)
		first_child(script, path_env, NULL);
	wait(&g_exit_status);
	if (WIFSIGNALED(g_exit_status))
		g_exit_status = 128 + WTERMSIG(g_exit_status);
	return (0);
}

/*
one_cmd(t_script *script, char **path_env) :
	This function is called if there is only one command to execute
	and differentiates the cmd between a builtin or another cmd.
*/
int	one_cmd(t_script *script, char **path_env)
{
	int	ret;

	ret = 0;
	if (script->commands[0].argv[0])
		ret = check_builtin(script->commands[0].argv[0]);
	if (ret == 2 || ret == 5
		|| (ret == 4 && script->commands[0].argv[1]) || ret == 7)
	{
		if (handle_builtin(ret, script, 0))
		{
			free_path_env(path_env);
			return (1);
		}
	}
	else
	{
		if (one_cmd_exec(script, path_env))
		{
			free_path_env(path_env);
			return (1);
		}
	}
	free_path_env(path_env);
	return (0);
}

/*
pipex(t_script *script, char **path_env) :
	This function is called if there are more than one command.
	It's the parent function for every fork and child that will be
	created in order for every command to be executed. It also waits for
	every fork process.
*/
int	pipex(t_script *script, char **path_env)
{
	int	pid;
	int	pipe1[2];
	int	pipe2[2];
	int	check;

	signal(SIGINT, sig_handler_fork);
	if (first_cmd(script, path_env, pipe1) == 1)
		return (1);
	check = mid_loop(script, path_env, pipe1, pipe2);
	if (check == -1)
		return (1);
	pid = fork();
	if (pid == -1)
		return (fork_error(path_env));
	if (check % 2 == 1)
		last_cmd(script, path_env, pipe2, pid);
	else
		last_cmd(script, path_env, pipe1, pid);
	wait(&g_exit_status);
	while (check-- > 0)
		wait(&g_exit_status);
	wait(&g_exit_status);
	if (WIFSIGNALED(g_exit_status))
		g_exit_status = 128 + WTERMSIG(g_exit_status);
	return (0);
}

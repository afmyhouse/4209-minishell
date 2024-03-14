/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   715_exec_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:25:54 by antoda-s          #+#    #+#             */
/*   Updated: 2024/03/13 22:20:37 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief 			Executes a single command script in a fork
/// @param s 		Script contents and parameters including redirect info
/// @param path		Commands execution path
/// @return			SUCCESS or ERROR
int	exec_one_fork(t_script *s, char **path)
{
	show_func(__func__, MY_START, NULL);
	int	pid;
	int	status;

	if (s->cmds[0].in.flag == -1)
		signal(SIGQUIT, SIG_IGN);
	else
		signal(SIGQUIT, sig_handler_fork);
	signal(SIGINT, sig_handler_fork);
	pid = fork();
	if (pid == -1)
		return (return_error("", errno, 1));
	if (pid == 0)
		ex_child_1(s, path, NULL);
	wait(&status);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	return (SUCCESS);
}

/// @brief 			Executes a single command script and checks if the command
///					is a builtin that doesnt need a fork (cd, unset, exit),
///					a builtin that requires a fork (echo, pwd, export, env)
///					or a system comamnd that requires a fork.
/// @param s 		Script contents and parameters including redirect info
/// @param path 	Commands execution path
/// @return 		SUCCESS or ERROR
int	exec_one(t_script *s, char **path)
{
	show_func(__func__, MY_START, NULL);
	int	id;

	id = CMD_EX;
	if (s->cmds[0].argv[0])
		id = exec_type(s->cmds[0].argv[0]);
	if (id == CMD_EQ)
		id = bi_equal_check(s, 0, 0);
	if (id == CMD_CD || (id == CMD_UNSET && s->cmds[0].argv[1])
		|| (id == CMD_EXPORT && s->cmds[0].argv[1]) || id == CMD_EXIT
		|| id == CMD_EQ)
	{
		if (exec_bi(id, s, 0))
			return (free_array(s->path, ERROR));
	}
	else if (exec_one_fork(s, s->path))
		return (free_array(s->path, ERROR));
	bi_env_upd(s, 0);
	return (free_array(s->path, SUCCESS));
}

int	exec_or(t_script *s, char **path)
{
	int	n;

	n = 0;
	printf("%s%s : n= %d : s->cmd_count = %d : g_exit_status = %d%s\n",
		SBHRED, __func__, n, s->cmd_count, g_exit_status, SRST);
	while (n < s->cmd_count)
	{
		if (!exec_one(s, path))
			break ;
		n++;
		printf("%s%s : n= %d : s->cmd_count = %d : g_exit_status = %d%s\n",
			SBHRED, __func__, n, s->cmd_count, g_exit_status, SRST);
	}
	return (SUCCESS);
}

int	exec_and(t_script *s, char **path)
{
	int	n;

	n = 0;
	while (n < s->cmd_count)
	{
		if (exec_one(s, path))
			break ;
		n++;
	}
	return (SUCCESS);
}

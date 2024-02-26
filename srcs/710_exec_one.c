/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   710_exec_one.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:25:54 by antoda-s          #+#    #+#             */
/*   Updated: 2024/02/26 01:52:25 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief 			Executes a builtin command according to its id
/// @param id 		Builtin command id
/// @param s 		Script contents and parameters including redirect info
/// @param i 		Index of the command to execute
/// @return 		SUCCESS or ERROR
int	exec_bi(int id, t_script *s, int i)
{
	show_func(__func__, MY_START, NULL);
	if (id == CMD_EQ)
		g_exit_status = bi_equal(s, i);
	else if (id == CMD_ECHO)
		g_exit_status = bi_echo(s, i);
	else if (id == CMD_CD)
		g_exit_status = bi_cd(s, i);
	else if (id == CMD_PWD)
		g_exit_status = bi_pwd(s, i);
	else if (id == CMD_EXPORT)
		g_exit_status = bi_export(s, i);
	else if (id == CMD_UNSET)
		g_exit_status = bi_unset(s, i);
	else if (id == CMD_ENV)
		g_exit_status = bi_env(s, i);
	else if (id == CMD_EXIT)
		return (bi_exit(s, i));
	show_func(__func__, SUCCESS, "bi executed");
	return (SUCCESS);
}

/// @brief 			Executes a command using the absolute path or the PATH
/// @param path 	Commands execution path
/// @param cmd 		Command to execute
/// @param env 		Environment variables
void	exec_ve(char **path, char **cmd, char **env)
{
	show_func(__func__, MY_START, NULL);
	char	*tmp;
	int		i;
	int		ret;

	tmp = ft_strdup(*cmd);
	i = 0;
	if (tmp[0] == '.' || tmp[0] == '/')
	{
		// falta atualizar a variável de ambiente SHLVL (o valor de SHLVL é incrementado em 1.)
		execve(*cmd, cmd, env);
		free(tmp); // se entrar no execve este free já nao acontece
		return ; // se entrar no execve este return já nao acontece
	}
	ret = -1;
	while (ret == -1 && path[i])
	{
		free(tmp);
		tmp = ft_strjoin(path[i], *cmd);
		if (!tmp)
			break ;
		ret = execve(tmp, cmd, env);
		i++;
	}
	if (tmp)
		free(tmp);
	//show_func(__func__, SUCCESS, NULL);
}

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
	{
		// return (fork_error(path));
		//free_array(path); // estava a ser feito no fork error mas o exec_one tb o faz if exec_one_fork
		return (return_error("", errno, 1)); // alterado filipe 20 fev
	}
	if (pid == 0)
	{
		show_func(__func__, SHOW_MSG,
			ft_strjoin("Exit_status antes de ex child: ", ft_itoa(g_exit_status)));
		ex_child_1(s, path, NULL);
	}
	wait(&status);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	//printf("Exit_status apos wait exec_one_fork: %d\n", g_exit_status);
	// if (WIFSIGNALED(status))
	// 	g_exit_status = 128 + WTERMSIG(status);
	//printf("Exit_status apos IF exec_one_fork: %d\n", g_exit_status);
	show_func(__func__, SUCCESS, "Parent ended");
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
	{
		show_func(__func__, SHOW_MSG, "<equal> checker");
		id = bi_equal_check(s, 0, 0);
		show_func(__func__, SHOW_MSG, "<equal> checker end");
	}
	if (id == CMD_CD || (id == CMD_UNSET && s->cmds[0].argv[1])
		|| (id == CMD_EXPORT && s->cmds[0].argv[1]) || id == CMD_EXIT
		|| id == CMD_EQ)
	{
		show_func(__func__, SHOW_MSG,  "exec_one parent : <cd>, <unset>, <export with args>, <exit>");
		if (exec_bi(id, s, 0))
		{
			free_array(path);
			show_func(__func__, ERROR, "exec_bi execution error");
			return (ERROR);
		}
	}
	else
	{
		show_func(__func__, SHOW_MSG, "exec_one child : <export without args>, <echo>, <env>, <pwd>, <execve>");
		if (exec_one_fork(s, path))
		{
			free_array(path); // o exec_one_forks faz free a path no fork_error se pid == -1, dava double free no env e pwd e deixou de dar
			show_func(__func__, ERROR, "exec_one_fork execution error");
			return (ERROR);
		}
	}
	bi_env_upd(s, 0);
	free_array(path);
	show_func(__func__, SUCCESS, "execute one succefully completed");
	return (SUCCESS);
}


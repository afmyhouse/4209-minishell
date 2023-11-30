/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 16:28:45 by mdeclerf          #+#    #+#             */
/*   Updated: 2021/10/07 17:31:19 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
exec_cmd( char **path, char **cmd, char **env) :
	This function first tries to execute the cmd using the absolute path then
	loops through the PATH until execve succeeds.
*/
static void	exec_cmd( char **path, char **cmd, char **env)
{
	char	*tmp;
	int		i;
	int		ret;

	tmp = ft_strdup(*cmd);
	i = 0;
	if (tmp[0] == '.' || tmp[0] == '/')
	{
		execve(*cmd, cmd, env);
		free(tmp);
		return ;
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
}

/*
cmd_builtin(t_script *script, char **path_env, int ret, int i) :
	This function is called in every child function. It differentiates between
	a builtin and another cmd and then executes it.
*/
void	cmd_builtin(t_script *script, char **path_env, int ret, int i)
{
	char		*tmp;
	struct stat	buf;

	if (!ret)
	{
		tmp = script->commands[i].argv[0];
		if (!tmp[0])
			return ;
		stat(tmp, &buf);
		exec_cmd(path_env, script->commands[i].argv, script->envp);
		if (S_ISDIR(buf.st_mode))
			errno = EISDIR;
		ft_putstr_fd("Minishell: ", 2);
		if (errno != ENOENT)
			perror(tmp);
		else
		{
			ft_putstr_fd(tmp, 2);
			ft_putendl_fd(": command not found", 2);
		}
		free_cmds_path(script, path_env);
		exit(127);
	}
	else
		handle_builtin(ret, script, i);
}

/*
handle_cmd(t_script *script) :
	This is the very first function that will be called every time
	we have a command, builtin or not. 
*/
int	handle_cmd(t_script *script)
{
	char	**path_env;

	path_env = split_paths(script->envp);
	if (script->cmd_count == 1)
	{
		if (one_cmd(script, path_env))
			return (1);
	}
	else
		if (pipex(script, path_env))
			return (1);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &script->termios_p);
	return (0);
}

int	check_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5))
		if (ft_strncmp(cmd, "cd", 3))
			if (ft_strncmp(cmd, "pwd", 4))
				if (ft_strncmp(cmd, "export", 7))
					if (ft_strncmp(cmd, "unset", 6))
						if (ft_strncmp(cmd, "env", 4))
							if (ft_strncmp(cmd, "exit", 5))
								return (0);
	else
		return (7);
	else
		return (6);
	else
		return (5);
	else
		return (4);
	else
		return (3);
	else
		return (2);
	else
		return (1);
}

int	handle_builtin(int ret, t_script *script, int i)
{
	if (ret == 1)
		g_exit_status = builtin_echo(script->commands[i]);
	if (ret == 2)
		g_exit_status = builtin_cd(script->commands[i], script->envp);
	if (ret == 3)
		g_exit_status = builtin_pwd(script->envp);
	if (ret == 4)
		g_exit_status = builtin_export(script, script->commands[i]);
	if (ret == 5)
		g_exit_status = builtin_unset(script, script->commands[i]);
	if (ret == 6)
		g_exit_status = builtin_env(script->envp, script->commands[i]);
	if (ret == 7)
		return (builtin_exit(script->commands[i], script->cmd_count,
				script->commands[i].argv[1]));
	return (0);
}

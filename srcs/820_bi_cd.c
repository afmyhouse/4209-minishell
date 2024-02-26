/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   820_bi_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 23:44:19 by antoda-s          #+#    #+#             */
/*   Updated: 2024/02/10 00:11:39 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief 			Changes the current directory and updates env var PWD OLDPWD
/// @param path 	New directory path
/// @param envp 	Environment variables
/// @return 		SUCCESS or ERROR
int	change_dir(char *path, char ***envp)
{
	show_func(__func__, MY_START, path);
	int		ret;
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, MAX_PATH_LEN);
	ret = chdir(path);
	if (ret == -1)
		return (return_error(path, 1, 1));
	env_var_setter(pwd, "OLDPWD", envp);
	pwd = NULL;
	pwd = getcwd(pwd, MAX_PATH_LEN);
	ret = env_var_setter(pwd, "PWD", envp);
	free(pwd);
	return (ret);
}

/// @brief 			Builtin cd command
/// @param args		Builtin command arguments
/// @return			SUCCESS or ERROR
int	bi_cd(t_script *s, int n)
{
	show_func(__func__, MY_START, ft_strjoin("execute bi: ", s->cmds[n].argv[0]));
	char	*home;
	int		status;

	env_var_setter(s->cmds[n].argv[s->cmds[n].argc - 1],"_", &s->envp);
	if (!s->cmds[n].argv[1])
	{
		//env_var_setter("cd","_", &s->envp);
		home = env_var_getter("HOME", s->envp, NULL);
		printf("HOME:%s\n", home); // este teste é pq se fizermos unset HOME, cd nao está a entrar no caso abaixo e deveria
		if (home == NULL)
		{
			//ft_putendl_fd("Minishell: cd: HOME not set", 2);
			free(home);
			return (return_error("Minishell: cd: HOME not set", 1, 0));
		}
		status = change_dir(home, &s->envp);
		free(home);
		return (status);
	}
	if (s->cmds[n].argc > 2)
	{
		//env_var_setter(s->cmds[n].argv[1],"_", &s->envp);
		// ft_putendl_fd("Minishell: cd: too many arguments", 2);
		//show_func(__func__, ERROR, NULL);
		return (return_error("Minishell: cd: too many arguments", 1, 0));
	}
	if (s->cmds[n].argv[1][0] == '\0')
	{
		status = change_dir(".", &s->envp);
		return (status);
	}
	//env_var_setter(s->cmds[n].argv[1],"_", &s->envp);
	status = change_dir(s->cmds[n].argv[1], &s->envp);
	return (status);
}

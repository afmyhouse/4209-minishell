/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoffaux <sgoffaux@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 14:56:14 by mdeclerf          #+#    #+#             */
/*   Updated: 2021/10/07 16:40:11 by sgoffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
get_env(char *str, char **envp) :
	This function returns the index position (in envp) of the name of the
	environment variable passed as a parameter.
*/
static int	get_env(char *str, char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(str, envp[i], ft_strlen(str)))
			return (i);
		i++;
	}
	return (-1);
}

/*
replace_env(char *str, char *name, char ***envp) :
	This function replaces an environment variable in envp. It is used
	to set OLDPWD to the correct path.
*/
static int	replace_env(char *str, char *name, char ***envp)
{
	int		idx;

	idx = get_env(name, *envp);
	if (idx == -1)
	{
		free(str);
		return (1);
	}
	free((*envp)[idx]);
	(*envp)[idx] = ft_strjoin_free(ft_strdup(name), str);
	return (0);
}

/*
change_dir(char *path, char ***envp) :
	This function changes the current directory with chdir(path) and
	replaces the environment variables $PWD and $OLDPWD.
*/
static int	change_dir(char *path, char ***envp)
{
	int		ret;
	char	*pwd;

	ret = chdir(path);
	if (ret == -1)
		return (return_error(path, 1));
	replace_env(get_env_content("PWD", *envp), "OLDPWD=", envp);
	pwd = NULL;
	pwd = getcwd(pwd, MAX_PATH_LEN);
	ret = replace_env(pwd, "PWD=", envp);
	return (ret);
}

/*
builtin_cd(t_command command, char **envp) :
	This function handles cd without arguments (leads to home), cd with too
	many arguments and a properly formated cd. 
*/
int	builtin_cd(t_command command, char **envp)
{
	char	*home;
	int		ret;

	if (!command.argv[1])
	{
		home = get_env_content("HOME", envp);
		if (!home[0])
		{
			ft_putendl_fd("Minishell: cd: HOME not set", 2);
			free(home);
			return (1);
		}
		ret = change_dir(home, &envp);
		free(home);
		return (ret);
	}
	if (command.argv[2])
	{
		ft_putendl_fd("Minishell: cd: too many arguments", 2);
		return (1);
	}
	if (command.argv[1][0] == '\0')
		return (change_dir(".", &envp));
	return (change_dir(command.argv[1], &envp));
}

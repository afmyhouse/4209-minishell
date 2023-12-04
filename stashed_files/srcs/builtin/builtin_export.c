/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeclerf <mdeclerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 14:55:39 by mdeclerf          #+#    #+#             */
/*   Updated: 2021/10/07 17:12:29 by mdeclerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
prep_bis(char *tmp, char *bis) : 
	Prepares bis to be compared with the env var names. 
*/
static void	prep_bis(char *tmp, char *bis)
{
	if (bis)
	{
		bis[0] = '=';
		bis[1] = '\0';
	}
	else
	{
		bis = ft_strnstr(tmp, "=", ft_strlen(tmp));
		if (bis)
			bis[0] = '\0';
	}
}

/*
check_existing_export(char **envp, char *str) : 
	Checks if the export arg already exists within the envp list. The
	char *bis is the export arg shortened until the = or +=.
*/
static int	check_existing_export(char **envp, char *str)
{
	int		i;
	char	*tmp;
	char	*bis;

	i = 0;
	tmp = ft_strdup(str);
	bis = ft_strnstr(tmp, "+=", ft_strlen(tmp));
	prep_bis(tmp, bis);
	while (envp[i])
	{
		if (!ft_strncmp(tmp, envp[i], ft_strlen(tmp)))
		{
			free(tmp);
			return (i);
		}
		i++;
	}
	free(tmp);
	return (0);
}

/*
prep_tmp_exist(char *argvar, char **tmp, const int ch, int i) : 
	This function is called in loopexport if the variable to export
	already exists. If the value to be exported has a += (means it has to
	be appended to the already existing var) we set everything after the += 
	to the end of the env var. Else the already existing var is freed and 
	replaced.
*/
static void	prep_tmp_exist(char *argvar, char **tmp, const int ch, int i)
{
	if (ft_strnstr(argvar, "+=", ft_strlen(argvar)))
		tmp[ch] = ft_strjoin_free(tmp[ch],
				ft_strdup(ft_strchr(argvar, '=') + 1));
	else
	{
		free(tmp[ch]);
		tmp[ch] = ft_strdup(argvar);
	}
	tmp[i] = NULL;
}

static void	loopexport(t_script *script, char **argv, int var, int len)
{
	int			exist;
	int			i;
	char		**tmp;
	const int	ch = check_existing_export(script->envp, argv[var]);

	exist = 0;
	if (ch)
		exist = 1;
	tmp = malloc(sizeof(char *) * (len + 2 - exist));
	if (!tmp)
		return ;
	i = copy_env(script->envp, tmp);
	if (exist)
		prep_tmp_exist(argv[var], tmp, ch, i);
	else
	{
		tmp[i] = copy_no_plus(argv[var]);
		if (!tmp[i])
			tmp[i] = ft_strdup(argv[var]);
		tmp[i + 1] = NULL;
	}
	free(script->envp);
	script->envp = tmp;
}

/*
builtin_export(t_script *script, t_command cmd) : 
	This function iterates through the args given to export, 
	check their validity and either adds or replace them in/to env.
	The variable err is used for cases like "export test" where
	nothing should be done but no error should be printed.
*/
int	builtin_export(t_script *script, t_command cmd)
{
	int	var;
	int	err;

	if (!script->envp || !cmd.argv[1] || cmd.argv[1][0] == '\0')
		return (export_check(script->envp, cmd));
	var = 1;
	err = 1;
	while (cmd.argv[var])
	{
		if (ft_isdigit(cmd.argv[var][0]) || !ft_strchr(cmd.argv[var], '=')
			|| !ft_strncmp(cmd.argv[var], "=", 1) || !checkvalid(cmd.argv[var]))
		{
			if (!checkvalid(cmd.argv[var]) || ft_isdigit(cmd.argv[var][0])
			|| !ft_strncmp(cmd.argv[var], "=", 1))
				error_message_export(cmd.argv[var]);
			if (!ft_strchr(cmd.argv[var], '='))
				err = 0;
			var++;
			continue ;
		}
		err = 0;
		loopexport(script, cmd.argv, var, env_len(script->envp));
		var++;
	}
	return (err);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeclerf <mdeclerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 14:56:08 by mdeclerf          #+#    #+#             */
/*   Updated: 2021/10/07 17:16:00 by mdeclerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
loopunset(t_script *script, char *arg, int len) : 
	Copies every env var into a new char ** tmp and skips one line if the 
	variable needs to be unset.
*/
static void	loopunset(t_script *script, char *arg, int len)
{
	int		i;
	int		j;
	char	*str;
	char	**tmp;

	tmp = malloc(sizeof(char *) * len);
	if (!tmp)
		return ;
	i = 0;
	j = 0;
	str = ft_strjoin(arg, "=");
	while (script->envp[i])
	{
		if (ft_strncmp(script->envp[i], str, ft_strlen(str)))
			tmp[j++] = script->envp[i];
		else
			free(script->envp[i]);
		i++;
	}
	free(str);
	tmp[j] = NULL;
	free(script->envp);
	script->envp = tmp;
}

/*
check_existing(t_script *script, t_command command, int var) : 
	Checks if the arg to unset exists in char **envp. It appends 
	a = to the variable to unset for cases where two env var would
	start the same and one would be longer.
*/
static int	check_existing(t_script *script, t_command command, int var)
{
	int		check;
	char	*tmp;
	int		i;

	i = 0;
	check = 0;
	tmp = ft_strjoin(command.argv[var], "=");
	while (script->envp[i])
	{
		if (!ft_strncmp(script->envp[i], tmp,
				ft_strlen(tmp)))
			check = 1;
		i++;
	}
	free(tmp);
	return (check);
}

/*
builtin_unset(t_script *script, t_command cmd) : 
	This function iterates through the args given to export, 
	check their validity (if they are not valid no error message 
	is displayed) and removes them from envp
*/
int	builtin_unset(t_script *script, t_command command)
{
	int		var;

	if (!script->envp)
		return (1);
	var = 1;
	while (command.argv[var])
	{
		if (!(check_existing(script, command, var)))
		{
			var++;
			continue ;
		}
		loopunset(script, command.argv[var], env_len(script->envp));
		var++;
	}
	return (0);
}

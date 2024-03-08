/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   840_bi_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 23:46:39 by antoda-s          #+#    #+#             */
/*   Updated: 2024/03/08 00:58:43 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief		Test validity of shell variables name
/// @param var	Variable name to be tested
/// @return		SUCCESS or ERROR
int	var_name_check(char *var)
{
	int	i;

	i = 0;
	if (var[i] && (!ft_isalpha(var[i]) || var[i] == '_'))
		return (ERROR);
	while (var[i] && var[i] != '=' && var[i] != '+')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
		{
			return (ERROR);
		}
		i++;
	}
	return (SUCCESS);
}

/// @brief  	Update the value of an existing variable either at envt or envp
/// @param s 	Script structure with commans and args
/// @param n 	Index of command to be executed
/// @param i 	Index of argument to be checked
void	bi_export_upd_var(t_script *s, int n, int i)
{
	char	*val;
	char	*var;

	var = ft_substr(s->cmds[n].argv[i], 0, ft_strlen(s->cmds[n].argv[i])
			- ft_strlen(ft_strchr(s->cmds[n].argv[i], '=')));
	val = ft_strdup(ft_strchr(s->cmds[n].argv[i], '=') + 1);
	env_var_setter(val, var, &s->envp);
	if (env_var_index_getter(var, s->envt) != -1)
		s->envt = env_del_one(var, s->envt, 0);
	free (var);
	free (val);
}

/// @brief  	Checks if export NEW environment variables or update existing
/// 			variables and also if the variables exist already in environment
/// 			temporary array
/// @param s 	Script structure with commans and args
/// @param n 	Index of command to be executed
/// @param i 	Index of argument to be checked
void	bi_export_new_var(t_script *s, int n, int i)
{
	char	*val;
	char	*var;
	int		j;

	var = s->cmds[n].argv[i];
	j = env_var_index_getter(var, s->envp);
	if (j >= 0)
		return ;
	j = env_var_index_getter(var, s->envt);
	if (j >= 0)
	{
		val = env_var_getter(var, NULL, s->envt);
		env_var_setter(val, var, &s->envp);
		s->envt = env_del_one(var, s->envt, 0);
		free(val);
	}
	else
		env_var_setter(NULL, var, &s->envp);
}

/// @brief 			Export PERMANENT environment variables
/// @param s 		Script structure with commans and args
/// @param n 		Index of command to be executed
/// @return 		SUCCESS or ERROR
int	bi_export(t_script *s, int n)
{
	int	i;

	if (!s->envp || !s->cmds[n].argv[1] || !s->cmds[n].argv[1][0])
		return (export_status(s, n));
	bi_append(s, n, 1);
	i = 1;
	while (s->cmds[n].argv[i])
	{
		if (var_name_check(s->cmds[n].argv[i]) == SUCCESS)
		{
			if (ft_strchr(s->cmds[n].argv[i], '='))
				bi_export_upd_var(s, n, i);
			else
				bi_export_new_var(s, n, i);
		}
		else
			export_error(s->cmds[n].argv[i], 1);
		i++;
	}
	return (SUCCESS);
}

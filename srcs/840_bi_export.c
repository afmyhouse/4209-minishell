/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   840_bi_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 23:46:39 by antoda-s          #+#    #+#             */
/*   Updated: 2024/02/26 00:16:10 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief		Test validity of shell variables name
/// @param var	Variable name to be tested
/// @return		SUCCESS or ERROR
int	var_name_check(char *var)
{
	show_func(__func__, MY_START, NULL);
	int	i;

	i = 0;
	//show_func(__func__, SHOW_MSG, var);
	if (var[i] && (!ft_isalpha(var[i]) || var[i] == '_'))
		return (ERROR);
	while (var[i] && var[i] != '=')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
		{
			//show_func(__func__, ERROR, NULL);
			return (ERROR);
		}
		i++;
	}
	//show_func(__func__, SUCCESS, NULL);
	return (SUCCESS);
}

/// @brief  	Update the value of an existing variable either at envt or envp
/// @param s 	Script structure with commans and args
/// @param n 	Index of command to be executed
/// @param i 	Index of argument to be checked
void	bi_export_upd_var(t_script *s, int n, int i)
{
	show_func(__func__, MY_START, NULL);
	char	*val;
	char	*var;

	var = ft_substr(s->cmds[n].argv[i], 0,
			ft_strlen(s->cmds[n].argv[i])
			- ft_strlen(ft_strchr(s->cmds[n].argv[i], '=')));
	//show_func(__func__, SHOW_MSG, ft_strjoin("var -> ", var));
	val = ft_strchr(s->cmds[n].argv[i], '=') + 1;
	//show_func(__func__, SHOW_MSG, ft_strjoin("val -> ", val));

	env_var_setter(val, var, &s->envp);
	if (env_var_index_getter(var, s->envt) != -1)
		bi_unset_envt(s, n);
	//show_func(__func__, SUCCESS, NULL);
}

/// @brief  	Checks if export NEW environment variables or update existing
/// 			variables and also if the variables exist already in environment
/// 			temporary array
/// @param s 	Script structure with commans and args
/// @param n 	Index of command to be executed
/// @param i 	Index of argument to be checked
void	bi_export_new_var(t_script *s, int n, int i)
{
	show_func(__func__, MY_START, NULL);
	char	*val;
	char	*var;

	var = s->cmds[n].argv[i];
	//show_func(__func__, SHOW_MSG, var);
	if (env_var_index_getter(var, s->envp) >= 0)
	{
		//show_func(__func__, SHOW_MSG, "var existes in P: exporting...\n");
		return ;
	}
	else if (s->envt && env_var_index_getter(var, s->envt) >= 0)
	{
		//show_func(__func__, SHOW_MSG, "var existes in T: exporting...\n");
		val = env_var_getter(var, NULL, s->envt);
		env_var_setter(val, var, &s->envp);
		bi_unset_envt(s, n);
	}
	else
	{
		//show_func(__func__, SHOW_MSG, "NEW var : creating without value");
		env_var_setter(NULL, var, &s->envp);
	}
	//show_func(__func__, SUCCESS, NULL);
}
void	export_print(char *s)
{
	char	*s1;
	char	*s2;

	if (!(s[0] == '_' && s[1] == '='))
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		if (!ft_strchr(s, '='))
			ft_putstr_fd(s, STDOUT_FILENO);
		else
		{
			s2 = ft_strjoin_free(ft_strdup(ft_strchr(s, '=') + 1),
					ft_strdup("\""));
			s1 = ft_strjoin_free(ft_substr(s, 0, ft_strlen(s)
						- ft_strlen(s2) + 1), ft_strdup("\""));
			ft_putstr_fd(s1, STDOUT_FILENO);
			ft_putstr_fd(s2, STDOUT_FILENO);
			free(s1);
			free(s2);
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
}

int	export_status(t_script *s, int n)
{
	int		i;
	char	**order;

	if (!s->cmds[n].argv[1])
	{
		if (!s->envp)
			return (1);
		i = -1;
		order = envp_init(s->envp);
		order = ordered_array(order, '=', 0, 0);
		while (order[++i])
			export_print(order[i]);
		free_array(order);
	}
	else if (s->cmds[n].argv[1][0] == '\0')
		return (return_error("Syntax error", 1, 2));
	return (SUCCESS);
}

/// @brief 			Export PERMANENT environment variables
/// @param s 		Script structure with commans and args
/// @param n 		Index of command to be executed
/// @return 		SUCCESS or ERROR
int	bi_export(t_script *s, int n)
{
	show_func(__func__, MY_START, NULL);
	int	i;

	if (!s->envp || !s->cmds[n].argv[1] || !s->cmds[n].argv[1][0])
		return (export_status(s, n));
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
	// show_func(__func__, SUCCESS, NULL);
	return (SUCCESS);
}

/// @brief 		Alphatecially ordered array
/// @param src 	Array to order
/// @return 	Ordered array
char	**ordered_array(char **d, char t, int n, int j)
{
	int	i;
	int	len_i;
	int	len_j;
	int	res_cmp;

	show_func(__func__, MY_START, "Ordering Array...");
	while (d[n] && d[n + 1])
	{
		j = n;
		i = j;
		while (d[++j])
		{
			len_i = ft_strchr(d[i], t) - d[i];
			len_j = ft_strchr(d[j], t) - d[j];
			res_cmp = ft_strncmp(d[i], d[j], ft_min(len_i, len_j));
			if (res_cmp > 0 || (res_cmp == 0 && len_i > len_j))
				i = j;
		}
		ft_strswap(&d[n++], &d[i]);
	}
	show_func(__func__, SUCCESS, "Array ordered...");
	return (d);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   880_bi_equal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 00:14:30 by antoda-s          #+#    #+#             */
/*   Updated: 2024/03/07 22:19:03 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief 			Update EXISTING TEMPORARY environment variables
/// @param s 		Script structure with commans and args
/// @param n 		Index of command to be executed
/// @param i 		Index of argument to be checked
void	bi_equal_upd(t_script *s, int n, int i)
{
	char	*var;
	char	*val;

	var = ft_substr(s->cmds[n].argv[i], 0, ft_strlen(s->cmds[n].argv[i])
			- ft_strlen(ft_strchr(s->cmds[n].argv[i], '=')));
	val = ft_strdup(ft_strchr(s->cmds[n].argv[i], '=') + 1);
	env_var_setter(val, var, &s->envp);
	ft_free(var);
	ft_free(val);
}

/// @brief 			Creates NEW TEMPORARY environment variables
/// @param s 		Script structure with commans and args
/// @param n 		Index of command to be executed
/// @param i 		Index of argument to be checked
void	bi_equal_new(t_script *s, int n, int i)
{
	char	*var;
	char	*val;

	var = ft_substr(s->cmds[n].argv[i], 0, ft_strlen(s->cmds[n].argv[i])
			- ft_strlen(ft_strchr(s->cmds[n].argv[i], '=')));
	val = ft_strdup(ft_strchr(s->cmds[n].argv[i], '=') + 1);
	env_var_setter(val, var, &s->envt);
	ft_free(var);
	ft_free(val);
}

/// @brief 			Export TEMPORARY environment variables
/// @param s 		Script structure with commans and args
/// @param n 		Index of command to be executed
/// @return 		SUCCESS or ERROR
int	bi_equal(t_script *s, int n)
{
	int		i;
	char	*var;

	if (!s->envp || !s->cmds[n].argv[0])
		return (ERROR);
	env_var_setter("", "_", &s->envp);
	i = -1;
	while (s->cmds[n].argv[++i])
	{
		if (var_name_check(s->cmds[n].argv[i]) == SUCCESS)
		{
			var = ft_substr(s->cmds[n].argv[i], 0, ft_strlen(s->cmds[n].argv[i])
					- ft_strlen(ft_strchr(s->cmds[n].argv[i], '=')));
			if (env_var_index_getter(var, s->envp) != -1)
				bi_equal_upd(s, n, i);
			else
				bi_equal_new(s, n, i);
			ft_free(var);
		}
		else
			export_error(s->cmds[n].argv[i], 1);
	}
	return (SUCCESS);
}

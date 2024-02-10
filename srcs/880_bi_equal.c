/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   880_bi_equal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 00:14:30 by antoda-s          #+#    #+#             */
/*   Updated: 2024/02/10 00:14:38 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief 			Update EXISTING TEMPORARY environment variables
/// @param s 		Script structure with commans and args
/// @param n 		Index of command to be executed
/// @param i 		Index of argument to be checked
void	bi_equal_upd(t_script *s, int n, int i)
{
	env_var_setter(ft_strchr(s->cmds[n].argv[i], '=') + 1,
		ft_substr(s->cmds[n].argv[i], 0,
			ft_strlen(s->cmds[n].argv[i])
			- ft_strlen(ft_strchr(s->cmds[n].argv[i], '='))),
		&s->envp);
}

/// @brief 			Creates NEW TEMPORARY environment variables
/// @param s 		Script structure with commans and args
/// @param n 		Index of command to be executed
/// @param i 		Index of argument to be checked
void	bi_equal_new(t_script *s, int n, int i)
{
	env_var_setter(ft_strchr(s->cmds[n].argv[i], '=') + 1,
		ft_substr(s->cmds[n].argv[i], 0,
			ft_strlen(s->cmds[n].argv[i])
			- ft_strlen(ft_strchr(s->cmds[n].argv[i], '='))),
		&s->envt);
}

/// @brief 			Export TEMPORARY environment variables
/// @param s 		Script structure with commans and args
/// @param n 		Index of command to be executed
/// @return 		SUCCESS or ERROR
int	bi_equal(t_script *s, int n)
{
	//show_func(__func__, MY_START, NULL);
	int		i;
	int		index_tp;

	env_var_setter("","_", &s->envp);
	if (!s->envp || !s->cmds[n].argv[0])
		return (ERROR);
	i = -1;
	while (s->cmds[n].argv[++i])
	{
		if (var_name_check(s->cmds[n].argv[i]) == SUCCESS)
		{
			index_tp = env_var_index_getter(ft_substr(s->cmds[n].argv[i], 0,
						ft_strlen(s->cmds[n].argv[i])
						- ft_strlen(ft_strchr(s->cmds[n].argv[i], '='))),
					s->envp);
			if (index_tp != -1)
				bi_equal_upd(s, n, i);
			else
				bi_equal_new(s, n, i);
		}
		else
			export_error(s->cmds[n].argv[i], 1);
	}
	//show_func(__func__, SUCCESS, NULL);
	return (SUCCESS);
}

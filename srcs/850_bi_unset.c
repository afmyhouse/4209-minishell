/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   850_bi_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 23:46:53 by antoda-s          #+#    #+#             */
/*   Updated: 2024/03/07 21:55:32 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief 			Remove a variable from the PERMANENT environment
/// @param s 		Arguments passed to unset command
/// @param n 		Current argument (variable)
/// @return			Updated environment variables
int	bi_unset(t_script *s, int n)
{
	// show_func(__func__, MY_START, NULL);
	int		i;
	char	*var;

	env_var_setter(s->cmds[n].argv[s->cmds[n].argc - 1], "_", &s->envp);
	if (!s->envp || !s->cmds[n].argv[1])
		return (ERROR);
	i = 1;
	while (s->cmds[n].argv[i])
	{
		var = s->cmds[n].argv[i];
		if (!ft_strchr(var, '='))
		{
			if (env_var_index_getter(var, s->envp) >= 0)
				s->envp = env_del_one(var, s->envp, 0);
			if (env_var_index_getter(var, s->envt) >= 0)
				s->envt = env_del_one(var, s->envt, 0);
		}
		i++;
	}
	//show_func(__func__, SUCCESS, NULL);
	return (SUCCESS);
}

/// @brief 			Remove a variable from the TEMPORARY environment
/// @param s 		Arguments passed to unset command
/// @param n 		Current argument (variable)
/// @return			Updated environment variables
int	bi_unset_envt(t_script *s, int n)
{
	// show_func(__func__, MY_START, NULL);

	int		i;
	int		j;
	char	*var;


	//show_func(__func__, SHOW_MSG, ft_itoa(n));

	if (!s->envt || !s->cmds[n].argv[1])
		return (ERROR);
	//show_func(__func__, SHOW_MSG, ft_strdup("before while..."));


	i = 1;
	while (s->cmds[n].argv[i])
	{
		if (!ft_strchr(s->cmds[n].argv[i], '='))
		{
			//show_func(__func__, SHOW_MSG, ft_strdup("inside while..."));
			j = env_var_index_getter(s->cmds[n].argv[i], s->envt);
			while (j >= 0 && s->envt[j] && s->envt[j + 1])
			{
				var = s->envp[j];
				s->envt[j] = ft_strdup(s->envt[j + 1]);
				free(var);
				j++;
			}
			s->envt[j] = NULL;
		}
		i++;
	}
	//show_func(__func__, SUCCESS, NULL);
	return (SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   850_bi_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 23:46:53 by antoda-s          #+#    #+#             */
/*   Updated: 2024/03/18 09:28:55 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief 			Remove a variable from the PERMANENT environment
/// @param s 		Arguments passed to unset command
/// @param n 		Current argument (variable)
/// @return			Updated environment variables
int	bi_unset(t_script *s, int n)
{
	show_func(__func__, MY_START, NULL);
	int		i;
	char	*var;

	env_var_setter(s->cmds[n].argv[s->cmds[n].argc - 1], "_", &s->envp);
	if (!s->envp || !s->cmds[n].argv[1])
		return (ERROR);
	i = 0;
	while (s->cmds[n].argv[++i])
		if (s->cmds[n].argv[i][0] == '-')
			return (flags_error(s->cmds[n].argv[0], s->cmds[n].argv[i], 0));
	i = 0;
	while (s->cmds[n].argv[++i])
	{
		var = s->cmds[n].argv[i];
		if (!ft_strchr(var, '='))
		{
			if (env_var_index_getter(var, s->envp) >= 0)
				s->envp = env_del_one(var, s->envp, 0);
			if (env_var_index_getter(var, s->envt) >= 0)
				s->envt = env_del_one(var, s->envt, 0);
		}
		//i++;
	}
	return (SUCCESS);
}

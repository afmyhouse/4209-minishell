/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   860_bi_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 00:09:56 by antoda-s          #+#    #+#             */
/*   Updated: 2024/04/04 00:51:58 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief 			Builtin env command
/// @param args		Builtin command arguments
/// @param envp		Environment variables
/// @return			SUCCESS or ERROR
int	bi_env(t_script *s, int n)
{
	show_func(__func__, FSTART, NULL);
	int	count;
	int	i;

	env_var_setter("env", "_", &s->envp);
	(void)n;
	i = 0;
	while (s->cmds[n].argv[++i])
		if (s->cmds[n].argv[i][0] == '-')
			return (error_bi_flags(s->cmds[n].argv[0], s->cmds[n].argv[i], 0));
	count = 0;
	while (s->envp[count] != NULL)
	{
		if (ft_strchr(s->envp[count], '='))
		{
			write(STDOUT_FILENO, s->envp[count], ft_strlen(s->envp[count]));
			write(STDOUT_FILENO, "\n", 1);
		}
		count++;
	}
	return (count);
}

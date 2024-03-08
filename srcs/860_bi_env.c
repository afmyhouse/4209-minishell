/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   860_bi_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 00:09:56 by antoda-s          #+#    #+#             */
/*   Updated: 2024/03/08 00:09:31 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief 			Builtin env command
/// @param args		Builtin command arguments
/// @param envp		Environment variables
/// @return			SUCCESS or ERROR
int	bi_env(t_script *s, int n)
{
	int	count;

	env_var_setter("env", "_", &s->envp);
	(void)n;
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

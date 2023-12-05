/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7ms_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 09:55:51 by antoda-s          #+#    #+#             */
/*   Updated: 2023/12/05 00:26:55 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/// @brief 			Script exec function
/// @param s 	Script contents
int	execute(t_script *s)
{
	int	i = -1;

	show_func(__func__, MY_START);
	printf("s->commands->cmd: %p\n", s->commands->cmd);
	printf("s->commands->argc: %i\n", s->commands->argc);
	while (++i < s->commands->argc)
	{
		printf("# s->commands->argv[%i]: %s\n",
			i, s->commands->argv[i]);
	}
	printf("s->commands->out.name: %s\n", s->commands->out.name);
	printf("s->commands->out.flag: %d\n", s->commands->out.flag);
	printf("s->commands->out->heredoc: %p\n", s->commands->out.heredoc);

	printf("s->commands->in.name: %s\n", s->commands->in.name);
	printf("s->commands->in.flag: %d\n", s->commands->in.flag);
	printf("s->commands->out->heredoc: %p\n", s->commands->in.heredoc);




	show_func(__func__, SUCCESS);
	return (SUCCESS);
}

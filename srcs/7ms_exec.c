/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7ms_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 09:55:51 by antoda-s          #+#    #+#             */
/*   Updated: 2023/12/14 14:41:50 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


static void	execute_show(t_script *s)
{
	show_func(__func__, MY_START);
	int	i = -1;
	int	j = -1;

	printf("s->com_count: %i\n", s->cmd_count);

	while (++j < s->cmd_count)
	{
		printf("\n");
		while (++i < s->commands[j].argc)
		{
			printf("# s->commands[%i].argv[%i]: %s\n", j, i, s->commands[j].argv[i]);
		}
		printf("  s->commands[%i].out.name: %s\n", j, s->commands[j].out.name);
		printf("  s->commands[%i].out.flag: %d\n", j, s->commands[j].out.flag);
		printf("  s->commands[%i].out->heredoc: %p\n", j, s->commands[j].out.heredoc);

		printf("  s->commands[%i].in.name: %s\n", j, s->commands[j].in.name);
		printf("  s->commands[%i].in.flag: %d\n", j, s->commands[j].in.flag);
		printf("  s->commands[%i].in->heredoc: %p\n", j, s->commands[j].in.heredoc);
		i = -1;
	}
	printf("\n");
	show_func(__func__, SUCCESS);
	return ;
}
/// @brief 		Script exec function
/// @param s 	Script contents
int	execute(t_script *s)
{
	show_func(__func__, MY_START);
	//char	**path_env;

	execute_show(s);
	// path_env = split_paths(s->envp);
	// if (s->cmd_count == 1)
	// {
	// 	if (one_cmd(s, path_env))
	// 		return (1);
	// }
	// else
	// 	if (pipex(s, path_env))
	// 		return (1);
	termios_setter(&s->termios_p);
	show_func(__func__, SUCCESS);
	return (SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoffaux <sgoffaux@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 16:08:33 by sgoffaux          #+#    #+#             */
/*   Updated: 2021/10/08 14:56:50 by sgoffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_commands(t_command *cmd, int cmd_idx)
{
	int	i;
	int	j;

	i = -1;
	while (++i < cmd_idx)
	{
		j = -1;
		while (++j < cmd[i].argc)
			if (cmd[i].argv[j])
				free(cmd[i].argv[j]);
		if (cmd[i].in.name)
			free(cmd[i].in.name);
		if (cmd[i].out.name)
			free(cmd[i].out.name);
		if (cmd[i].in.heredoc)
			ft_lstclear(&cmd[i].in.heredoc, free);
		free(cmd[i].argv);
	}
	free(cmd);
	return (1);
}

int	free_tokens(t_token **head)
{
	t_token	*tmp;

	while (*head)
	{
		tmp = (*head)->next;
		free((*head)->content);
		free(*head);
		*head = tmp;
	}
	return (1);
}

void	free_path_env(char **path_env)
{
	int	i;

	i = 0;
	while (path_env[i])
	{
		free(path_env[i]);
		i++;
	}
	free(path_env);
}

void	free_cmds_path(t_script *script, char **path_env)
{
	free_commands(script->commands, script->cmd_count);
	free_path_env(path_env);
}

void	close_free_exit(t_script *s, char **path_env, int *p1, int *p2)
{
	free_cmds_path(s, path_env);
	close_pipes(p1, p2);
	exit(1);
}

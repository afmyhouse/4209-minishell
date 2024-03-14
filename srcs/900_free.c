/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   900_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:26:48 by antoda-s          #+#    #+#             */
/*   Updated: 2024/03/13 23:11:55 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief 			Frees the environment variables
/// @param my_envp	Environment variables
int	free_array(char **array, int err)
{
	int	i;

	if (!array)
		return (err);
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (err);
}

/// @brief 		Frees the token list
/// @param head	Head of the token list
/// @return		1 if success, 0 if failure
int	free_tokens(t_token **tk)
{
	t_token	*tmp;

	if (!tk)
		return (ERROR);
	while (*tk)
	{
		tmp = (*tk)->next;
		free((*tk)->content);
		free(*tk);
		*tk = tmp;
	}
	return (1);
}

/// @brief 			Clears args on cmds struct list and frees nodes
/// @param cmd 		list pointer
/// @param cmd_idx 	quantity of nodes to clear and free
/// @return 		SUCCESS or ERROR ?? needs coherence check
int	free_commands(t_command *cmd, int cmd_idx)
{
	int	i;
	int	j;

	i = -1;
	while (++i < cmd_idx)
	{
		j = -1;
		while (++j < cmd[i].argc)
		{
			if (cmd[i].argv[j])
				ft_free(cmd[i].argv[j]);
		}
		free(cmd[i].argv);
		if (cmd[i].in.name)
			ft_free(cmd[i].in.name);
		if (cmd[i].out.name)
			ft_free(cmd[i].out.name);
		if (cmd[i].in.heredoc)
			ft_lstclear(&cmd[i].in.heredoc, free);
	}
	if (cmd)
		free(cmd);
	return (1);
}

/// @brief 		Frees the path, envt, envp and the commands
/// @param s 	Struct with pointer to be freed
int	free_exit(t_script *s, int errms)
{
	free_commands(s->cmds, s->cmd_count);
	free_array(s->path, 0);
	free_array(s->envt, 0);
	free_array(s->envp, 0);
	return (errms);
}

/// @brief 			Frees the path and the commands
/// @param script 	Script to be freed
/// @param path 	Path to be freed
void	free_cmds_path(t_script *script, char **path)
{
	free_commands(script->cmds, script->cmd_count);
	free_array(path, 0);
}

/// @brief 			Shows error and program sourcing it and exit(1) freeing
/// 				allocated vars
/// @param msg 		Message to show
/// @param errms 	Error message
/// @param s 		Script to be freed
/// @param path 	Path to be freed
void	exit_forks(char *msg, int errms, t_script *s, char **path)
{
	return_error(msg, errms, 1);
	free_cmds_path(s, path);
	exit(1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   900_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:26:48 by antoda-s          #+#    #+#             */
/*   Updated: 2024/02/25 20:13:48 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief 			Frees the environment variables
/// @param my_envp	Environment variables
void	free_array(char **array)
{

	show_func(__func__, MY_START, NULL);
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	show_func(__func__, SUCCESS, "Array freed");
}

/// @brief 		Frees the token list
/// @param head	Head of the token list
/// @return		1 if success, 0 if failure
int	free_tokens(t_token **head)
{
	t_token	*tmp;

	if (!head)
		return (ERROR);
	while (*head)
	{
		tmp = (*head)->next;
		free((*head)->content);
		free(*head);
		*head = tmp;
	}
	return (1);
}

/// @brief 			Clears args on cmds struct list and frees nodes
/// @param cmd 		list pointer
/// @param cmd_idx 	quantity of nodes to clear and free
/// @return 		SUCCESS or ERROR ?? needs coherence check
int	free_commands(t_command *cmd, int cmd_idx)
{
	show_func(__func__, MY_START, NULL);
	show_func(__func__, SHOW_MSG, ft_strjoin("cmd_idx = ", ft_itoa(cmd_idx)));
	int	i;
	int	j;

	i = -1;
	while (++i < cmd_idx)
	{
		j = -1;
		while (++j < cmd[i].argc)
		{
			show_func(__func__, SHOW_MSG, ft_strjoin("cmd = ", cmd[i].argv[j] ));
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
	free(cmd);
	show_func(__func__, SUCCESS, NULL);
	return (1);
}

/// @brief 			Frees the path and the commands
/// @param script 	Script to be freed
/// @param path 	Path to be freed
void	free_cmds_path(t_script *script, char **path)
{
	show_func(__func__, MY_START, NULL);
	free_commands(script->cmds, script->cmd_count);
	free_array(path);
	show_func(__func__, SUCCESS, NULL);
}

/// @brief 			Shows error and program sourcing it and exit(1) freeing
/// 				allocated vars
/// @param msg 		Message to show
/// @param errms 	Error message
/// @param s 		Script to be freed
/// @param path 	Path to be freed
void	exit_forks(char *msg, int errms, t_script *s, char **path)
{
	show_func(__func__, MY_START, NULL);
	return_error(msg, errms, 1);
	free_cmds_path(s, path);
	//show_func(__func__, SUCCESS, NULL);
	exit(1);
}

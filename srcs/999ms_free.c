/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   999ms_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:26:48 by antoda-s          #+#    #+#             */
/*   Updated: 2023/12/13 22:35:48 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/// @brief 			Frees the environment variables
/// @param my_envp	Environment variables
void	free_envp(char **my_envp)
{
	int	i;

	show_func(__func__, MY_START);
	i = 0;
	while (my_envp[i])
	{
		free(my_envp[i]);
		i++;
	}
	free(my_envp);
	show_func(__func__, SUCCESS);
}

/// @brief 			Frees the content of a split string
/// @param split	Split string to be freed
void	free_split(char **split)
{
	int	i;

	show_func(__func__, MY_START);
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	show_func(__func__, SUCCESS);
}

/// @brief 		Frees the token list
/// @param head	Head of the token list
/// @return		1 if success, 0 if failure
int	free_tokens(t_token **head)
{
	t_token	*tmp;

	show_func(__func__, MY_START);
	while (*head)
	{
		tmp = (*head)->next;
		free((*head)->content);
		free(*head);
		*head = tmp;
	}
	show_func(__func__, SUCCESS);
	return (1);
}

/// @brief 			Clears args on commands struct list and frees nodes
/// @param cmd 		list pointer
/// @param cmd_idx 	quantity of nodes to clear and free
/// @return 		SUCCESS or ERROR ?? needs coherence check
int	free_commands(t_command *cmd, int cmd_idx)
{
	show_func(__func__, MY_START);
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
	show_func(__func__, SUCCESS);
	return (1);
}


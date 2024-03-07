/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   304_parser_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 23:28:14 by antoda-s          #+#    #+#             */
/*   Updated: 2024/03/02 01:13:53 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief 		Iniatilzes file names direction
/// @param cmds Struct with info about files
/// @param max 	max number of files
/// @param tk 	pointert o command struct hed
void	fnames_clear(t_command *cmds, int max, t_token *tk)
{
	int	i;

	(void)tk;
	i = -1;
	while (++i < max)
	{
		cmds[i].in.name = NULL;
		cmds[i].out.name = NULL; //??
		cmds[i].in.heredoc = NULL;
		cmds[i].in.flag = -1;
		cmds[i].out.flag = -1;
	}
	return ;
}

/// @brief 			This function sets the open flags and opens the files
///					based on the type of redirection token it encounters
///					('<', '<<', '>', '>>').
/// @param tk		Head of the token list
/// @param file		Redirection file structure
/// @return			0 if success, 1 if failure
int	redir(t_token *tk, t_redirection *file)
{
	// show_func(__func__, MY_START, NULL);
	int		ret;

	if (file->name)
		free(file->name);
	if (!tk->next || tk->next->type != TK_NAME)
		return (SUCCESS);
	file->name = ft_strdup(tk->next->content);
	if (!ft_strncmp(tk->content, ">>", 2))
		file->flag = (O_CREAT | O_APPEND | O_RDWR);
	else if (!ft_strncmp(tk->content, "<<", 2))
		fill_heredoc(file);
	else if (!ft_strncmp(tk->content, ">", 1))
		file->flag = (O_CREAT | O_TRUNC | O_RDWR);
	else if (!ft_strncmp(tk->content, "<", 1))
		file->flag = O_RDONLY;
	if (file->flag == -1)
		return (SUCCESS);
	ret = open(file->name, file->flag, 0644);
	if (ret == -1)
		return (return_error(file->name, 0, 1));
	close(ret);
	return (SUCCESS);
}

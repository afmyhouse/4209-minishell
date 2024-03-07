/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   305_parser_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 23:28:14 by antoda-s          #+#    #+#             */
/*   Updated: 2024/03/02 01:13:53 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief 		Creates a node in the file linked list withe file name
///				and adds it to the back of list
/// @param file	Struct linked list node
void	fill_heredoc(t_redirection *file)
{
	t_list	*tmp;

	// show_func(__func__, MY_START, NULL);
	tmp = ft_lstnew(ft_strdup(file->name));
	if (file->heredoc == NULL)
		file->heredoc = tmp;
	else
		ft_lstadd_back(&file->heredoc, tmp);
	file->flag = -1;
	//show_func(__func__, SUCCESS, NULL);
}

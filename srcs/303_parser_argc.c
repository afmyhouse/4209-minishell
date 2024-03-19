/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   303_parser_argc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 23:28:14 by antoda-s          #+#    #+#             */
/*   Updated: 2024/03/19 00:04:03 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//// @brief		This function determines the amount of arguments each command
///				has so the argv can be malloced to the right size in the
///				following steps.
/// @param tk	Head of the token list
/// @param s	Script pointer
/// @return		Trimmed content
void	args_counter(t_token *tk, t_script *s)
{
	t_token	*tmp;
	int		i;

	i = 0;
	while (i < s->cmd_count)
	{
		s->cmds[i].argc = 0;
		tmp = tk;
		while (tk && tk->type != TK_PIPE)
		// while (tk && (tk->type != TK_PIPE && tk->type != TK_OR))
		{
			if (tk->type == TK_NAME && (tmp->type != TK_I
					&& tmp->type != TK_O))
				s->cmds[i].argc++;
			tmp = tk;
			tk = tk->next;
		}
		if (tk)
			tk = tk->next;
		i++;
	}
	return ;
}

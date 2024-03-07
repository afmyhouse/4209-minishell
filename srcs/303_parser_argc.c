/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   303_parser_argc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 23:28:14 by antoda-s          #+#    #+#             */
/*   Updated: 2024/03/02 01:13:53 by antoda-s         ###   ########.fr       */
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
	// show_func(__func__, MY_START, NULL);
	t_token	*tmp;
	int		i;

	i = 0;
	while (i < s->cmd_count)
	{
		s->cmds[i].argc = 0;
		tmp = tk;
		while (tk && tk->type != TK_PIPE)
		{
			if (tk->type == TK_NAME && (tmp->type != TK_R_IN
					&& tmp->type != TK_R_OUT))
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

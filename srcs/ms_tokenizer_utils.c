/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:24:28 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/29 21:33:09 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"



/// @brief 				Adds new token to token list end
/// @param head		Head of the token list
/// @param new		New token to be added
void	add_token(t_token **head, t_token *new)
{
	t_token	*tmp;

	if (!head || !new)
		return ;
	if (!*head)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}


/// @brief 			Searches for a token type by token char set
/// @param s		String to be searched for token char set
/// @return			Struct with token type information: token char set, size
///					and token type
t_operations	search_token_type(const char *s)
{
	t_operations	ex_ops[12];
	t_operations	blank;
	int				i;

	blank = (t_operations){0, 0, 0};
	ex_ops[0] = (t_operations){">>", 2, TOKEN_R_OUT};
	ex_ops[1] = (t_operations){"<<", 2, TOKEN_R_IN};
	ex_ops[2] = (t_operations){"|", 1, TOKEN_PIPE};
	ex_ops[3] = (t_operations){">", 1, TOKEN_R_OUT};
	ex_ops[4] = (t_operations){"<", 1, TOKEN_R_IN};
	ex_ops[5] = (t_operations){" ", 1, TOKEN_WS};
	ex_ops[7] = (t_operations){"\v", 1, TOKEN_WS};
	ex_ops[8] = (t_operations){"\t", 1, TOKEN_WS};
	ex_ops[9] = (t_operations){"\r", 1, TOKEN_WS};
	ex_ops[10] = (t_operations){"\f", 1, TOKEN_WS};
	ex_ops[11] = (t_operations){NULL, 1, 0};
	i = -1;
	while (ex_ops[++i].op)
		if (!ft_strncmp(s, ex_ops[i].op, ex_ops[i].size))
			return (ex_ops[i]);
	return (blank);
}

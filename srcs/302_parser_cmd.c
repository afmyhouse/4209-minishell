/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   302_parser_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 23:28:14 by antoda-s          #+#    #+#             */
/*   Updated: 2024/03/07 22:59:48 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief		This function simply counts the number of pipes in our
///				linked list of tokens to determine the number of chained
///				cmds are in the line buffer.
/// @param tk	Head of the token list
/// @return		Number of cmds
int	cmds_counter(t_token *tk)
{
	int	count;

	count = 0;
	while (tk)
	{
		if (!count)
			count = 1;
		if (tk->type == TK_PIPE)
			count ++;
		tk = tk->next;
	}
	return (count);
}

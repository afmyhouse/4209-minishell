/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:10:37 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/30 10:28:24 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	token_setter(char *str, t_token **head)
{
	t_operations	curr;
	char			*prev;

	prev = str;
	while (str && *str)
	{
		curr = search_token_type(str);
		if (curr.op != 0 && prev != str)
			add_token(head, create_token(prev, str - prev, TOKEN_NAME));
		if (curr.op != 0)
		{
			str += curr.size;
			if (curr.type != TOKEN_EMPTY)
				add_token(head)
		}
	}
}

// int	tokenizer(t_script *script, char *line)
// {
// 	int	i;

// 	i = 0;
// 	while (line[i] != '\0')
// 	{
// 		if (line[i] == ' ')
// 			i++;
// 		else if (line[i] == '\'')
// 			i = single_quote(script, line, i);
// 		else if (line[i] == '\"')
// 			i = double_quote(script, line, i);
// 		else if (line[i] == '$')
// 			i = dollar(script, line, i);
// 		else if (line[i] == '\\')
// 			i = backslash(script, line, i);
// 		else
// 			i = word(script, line, i);
// 	}
// 	return (SUCCESS);
// }
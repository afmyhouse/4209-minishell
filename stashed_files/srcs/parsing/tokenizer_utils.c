/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 16:12:47 by sgoffaux          #+#    #+#             */
/*   Updated: 2023/12/13 21:31:11 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
create_token(const char *string, int size, t_token_type type):
	This function simply mallocs and creates a token with the given type, size
	and content and returns it.
*/
t_token	*create_token(const char *string, int size, t_token_type type)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->content = ft_substr(string, 0, size);
	token->size = size;
	token->type = type;
	token->next = NULL;
	return (token);
}

/*
add_token(t_token **head, t_token *new_token):
	This function takes a token list node (new_token) and adds it to the end
	of the linked list pointed to by head.
*/
void	add_token(t_token **head, t_token *new_token)
{
	t_token	*tmp;

	if (new_token)
	{
		if (*head == NULL)
			*head = new_token;
		else
		{
			tmp = *head;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new_token;
		}
	}
}

/*
search_token_type(const char *s):
	This function compares the character(s) given to some possible operations and
	returns either the given operation if found, or a blank operation.
*/
t_ops	search_token_type(const char *s)
{
	const t_ops		ex_ops[12] =
	{
		{">>", 2, TOKEN_REDIR_OUT},
		{"<<", 2, TOKEN_REDIR_IN},
		{"|", 1, TOKEN_PIPE},
		{">", 1, TOKEN_REDIR_OUT},
		{"<", 1, TOKEN_REDIR_IN},
		{" ", 1, TOKEN_EAT},
		{"\n", 1, TOKEN_EAT},
		{"\v", 1, TOKEN_EAT},
		{"\t", 1, TOKEN_EAT},
		{"\r", 1, TOKEN_EAT},
		{"\f", 1, TOKEN_EAT},
		{NULL, 1, 0}
	};
	const t_ops		blank = {0, 0, 0};
	int						i;
	i = -1;
	while (ex_ops[++i].op)
		if (!ft_strncmp(s, ex_ops[i].op, ex_ops[i].size))
			return (ex_ops[i]);
	return (blank);
}

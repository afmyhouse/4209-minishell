/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   501_tk_builder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:10:37 by antoda-s          #+#    #+#             */
/*   Updated: 2024/03/25 15:02:57 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @attention	>token builder< set of functions
/// @brief 		Searches for a token type by token char set
/// @param s	String to be searched for token char set
/// @return		Struct with token type information: token char set, size
///				and token type
t_ops	tk_type_getter(const char *s)
{
	t_ops		blank;
	int			i;
	const t_ops	ops[16] = {{"<<", 2, TK_I}, {"<", 1, TK_I}, {">>", 2, TK_O},
	{">|", 2, TK_O}, {"<>", 2, TK_O}, {">", 1, TK_O},
	{" ", 1, TK_WS}, {"\n", 1, TK_WS}, {"\v", 1, TK_WS},
	{"\t", 1, TK_WS}, {"\r", 1, TK_WS}, {"\f", 1, TK_WS},
	{"||", 2, TK_OR}, {"&&", 2, TK_AND}, {"|", 1, TK_PIPE}, {NULL, 1, 0}};

	blank = (t_ops){0, 0, 0};
	i = -1;
	while (ops[++i].op)
	{
		if (!ft_strncmp(s, ops[i].op, ops[i].size))
			return (ops[i]);
	}
	return (blank);
}

/// @attention	>token builder< set of functions
/// @brief 		Initializes the tk_getter
/// @param str	String to be splitted in tokens
/// @param head	Head of the token list
/// @return		1 if success, 0 if error
int	tk_getter(char *str, t_token **tk_lst)
{
	t_ops	ptr;
	char	*prev;

	prev = str;
	while (str && *str)
	{
		ptr = tk_type_getter(str);
		if (ptr.op != 0 && prev != str)
			tk_lst_addback(tk_lst, tk_addnew(prev, str - prev, TK_NAME));
		if (ptr.op != 0)
		{
			str += ptr.size;
			if (ptr.type != TK_WS)
				tk_lst_addback(tk_lst, tk_addnew(ptr.op, ptr.size, ptr.type));
			prev = str;
		}
		else if ((*str == '\"' || *str == '\'') && tk_quotes_checker(&str))
			return (ERROR);
		else
			++str;
	}
	if (prev != str)
		tk_lst_addback(tk_lst, tk_addnew(prev, str - prev, TK_NAME));
	return (SUCCESS);
}

/// @attention	>token builder< set of functions
/// @brief 		Builds a list of tokens from string 'line'.
///				First it gets the proper token type and then expands the
///				the inset identifiers found, and also trims the tokens
///				extra whitespaces
/// @param line	string input with script
/// @param head	pointer to the head of the token list
/// @param s	script structure
/// @return		SUCCESS if valid, ERROR if invalid
int	tk_builder(char **line, t_token **tk, t_script *s)
{
	t_token	*tk_ptr;
	char	*content;

	if (tk_getter(*line, tk) == ERROR)
	{
		error_return("Syntax Error", 1, 0);
		return (ERROR);
	}
	tk_ptr = *tk;
	while (tk_ptr)
	{
		content = tk_ptr->content;
		if (content[0] == '~' && ft_strlen(content) == 1 && s->home)
			tk_ptr->content = ft_strdup(s->home);
		else
			tk_ptr->content = tk_env_var_expander(content, s);
		ft_free(content);
		tk_ptr = tk_ptr->next;
	}
	return (SUCCESS);
}

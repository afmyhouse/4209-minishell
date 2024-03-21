/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   500_tk_blank.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:10:37 by antoda-s          #+#    #+#             */
/*   Updated: 2024/03/20 17:13:11 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief 		detects the occurrence of char from set in string str
/// @param str	string to process
/// @param set	set of chars
/// @return		char found or 0
char	ft_strset(const char *str, const char *set)
{
	if (!str || !set)
		return ('\0');
	while (*set && !ft_strchr(str, *set))
		set++;
	return (*set);
}

/// @brief 		Remove blanks from composed litrals + vars
/// @param tk_p	head of tokenor previous token
/// @param tk	token
/// @param c	separator to comply removal
void	tk_blank_split(t_token **tk_p, t_token *tk, char c )
{
	char	*str;
	char	*tmp;
	t_token	*tk_new;

	if (!c)
		return ;
	*tk_p = NULL;
	str = tk->content;
	while (str && *str && c)
	{
		tk_new = tk_addnew(str, ft_strchr(str, c) - str, TK_NAME);
		tk_lst_addback(tk_p, tk_new);
		str = ft_strtrim(ft_strchr(str, c), " \t\v\r\n\f");
		c = ft_strset(str, " \t\v\r\n\f");
	}
	tmp = tk->content;
	tk->content = str;
	tk->size = ft_strlen(str);
	tk_new->next = tk;
	free(tmp);
	return ;
}

/// @attention	>token builder< set of functions
/// @brief 		This function is here to treat off cases where a $ expansion
///				would lead to empty name tokens with the exception for an empty
///				token after a pipe.
/// @param head Head of the token list
/// @return		clean content
void	tk_rm_blank(t_token **tk)
{
	t_token	**tk_p;
	t_token	*tk_n;

	if (!*tk || !tk)
		return ;
	tk_p = tk;
	tk_n = (*tk);
	while (tk_n)
	{
		if (tk_n->type == TK_NAME && !ft_strchr((*tk)->content, '='))
			tk_blank_split(tk_p, tk_n, ft_strset((*tk)->content,
					" \t\v\r\n\f"));
		tk_p = &(tk_n->next);
		tk_n = tk_n->next;
	}
	return ;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   500_tk_blank.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:10:37 by antoda-s          #+#    #+#             */
/*   Updated: 2024/04/04 00:50:28 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief 		Remove blanks from composed litrals + vars
/// @param tk_p	head of tokenor previous token
/// @param tk	token
/// @param c	separator to comply removal
void	tk_blank_split(t_token **tk_p, t_token *tk, char c )
{
	show_func(__func__, FSTART, NULL);
	char	*str1;
	char	*str2;
	char	*tmp;
	t_token	*tk_new;

	if (!c)
		return ;
	*tk_p = NULL;
	str1 = tk->content;
	while (str1 && *str1 && c)
	{
		tk_new = tk_addnew(str1, ft_strchr(str1, c) - str1, TK_NAME);
		tk_lst_addback(tk_p, tk_new);
		str2 = ft_strtrim(ft_strchr(str1, c), " \t\v\r\n\f");
		if (ft_strncmp(str1, tk->content, ft_strlen(tk->content)))
			ft_free(str1);
		str1 = str2;
		c = ft_strset(str1, " \t\v\r\n\f");
	}
	tmp = tk->content;
	tk->content = str1;
	tk->size = ft_strlen(str1);
	tk_new->next = tk;
	ft_free(tmp);
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
	show_func(__func__, FSTART, NULL);
	t_token	**tk_p;
	t_token	*tk_n;
	char	c;

	if (!*tk || !tk)
		return ;
	tk_p = tk;
	tk_n = (*tk);
	while (tk_n)
	{
		if (tk_n->type == TK_NAME && tk_n->rm)
		{
			c = ft_strset(tk_n->content, " \t\v\r\n\f");
			if (c)
				tk_blank_split(tk_p, tk_n, c);
		}
		tk_p = &(tk_n->next);
		tk_n = tk_n->next;
	}
	return ;
}

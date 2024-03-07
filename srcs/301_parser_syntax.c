/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   301_parser_syntax.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 23:28:14 by antoda-s          #+#    #+#             */
/*   Updated: 2024/03/02 01:13:53 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief 				Builds an error message string to be displayed
///						when a syntax error is encountered.
/// @malloc				New strings
/// @free				New strings
/// @param tk_content	String argument to include in the error message
/// @return				Error message string
int	syntax_error_msg(char *tk_content, int errms, int errsys)
{
	// show_func(__func__, MY_START, NULL);
	char	*msgr;
	char	*msgt;
	int		status;

	msgt = ft_strjoin("syntax error near unexpected token `", tk_content);
	msgr = ft_strjoin(msgt, "'");
	free(msgt);
	status = return_error(msgr, errms, errsys);
	free(msgr);
	return (status);
}

/// @brief		This function checks whether the given linked list, of tokens,
///				is a valid command syntaxically.
/// @param tk	Head of the token list
/// @return		0 if success, 1 if failure
int	syntax_checker(t_token *tk)
{
	// show_func(__func__, MY_START, NULL);
	if (tk && tk->type == TK_PIPE)
		return (syntax_error_msg(tk->content, 2, 0));
	while (tk)
	{
		if (!tk->next && (tk->type == TK_PIPE || tk->type == TK_R_IN
				|| tk->type == TK_R_OUT))
			return (syntax_error_msg(tk->content, 2, 0));
		if (tk->type == TK_PIPE && tk->next
			&& tk->next->type == TK_PIPE)
			return (syntax_error_msg(tk->next->content, 2, 0));
		if ((tk->type == TK_R_OUT || tk->type == TK_R_IN)
			&& (tk->next && tk->next->type != TK_NAME))
			return (syntax_error_msg(tk->next->content, 2, 0));
		tk = tk->next;
	}
	// show_func(__func__, SUCCESS, NULL);
	return (SUCCESS);
}

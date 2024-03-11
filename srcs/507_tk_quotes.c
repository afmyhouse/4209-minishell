/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   507_tk_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:10:37 by antoda-s          #+#    #+#             */
/*   Updated: 2024/03/10 23:51:47 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief 		fetchs for closed / unclosed quotes type " or '
///				the function must be called with the arg str (string)
///				starting with at a quotation mark.
///				The function seeks for the next occurrence of that quation mark
///				and sets str pointer to that next occurrence if found
///				or sets str pointer to the end {\0}
///				@malloc	: NOTHING
///				@free	: NOTHING
/// @param str	addres of the string to seek, that starts with a quotation mark
/// @return		ERROR (unclosed), SUCCES (closed)
int	tk_quotes_checker(char **str)
{
	show_func(__func__, MY_START, NULL);
	char	*tmp;

	tmp = *str;
	(*str) = ft_strchr((*str) + 1, **str);
	if (!(*str))
	{
		(*str) = tmp + ft_strlen(tmp);
		return (ERROR);
	}
	return (SUCCESS);
}

/// @brief 		Unquotes a string. Special rules applies
///				- removes ' from limits = 'string'
///				- removes " from limts = "string", "string, string"
///				- (')  and (") are never inspected inside string
///				@malloc	: NOTHING
///				@free	: NOTHING
/// @param str	String to be unquoted
/// @return		A new unquoted string
char	*tk_xpd_unquote(char *str)
{
	show_func(__func__, MY_START, NULL);
	char	*ret;
	int		len;

	ret = NULL;
	len = ft_strlen(str);
	if (str[0] == '\'' || (str[0] == '\"' && str[len - 1] == '\"'))
		ret = ft_substr(str, 1, len - 2);
	else if (str[0] == '\"' && str[len - 1] != '\"')
		ret = ft_strdup(str + 1);
	else if (str[0] != '\"' && str[len - 1] == '\"')
		ret = ft_substr(str, 0, len - 1);
	else if (str[0] != '\"' && str[len - 1] != '\"')
		ret = ft_strdup(str);
	free(str);
	return (ret);
}

/// @brief			Replaces the token->content string with a new trimmed string
///					Trim removes leading and trailing white spaces
///	@malloc			TRIMMED string
///	@free			Pre TRIM string
/// @param tk	Head of the token list with token->content to be trimmed
/// @return			NOTHING
void	tk_trim_spaces(t_token *tk)
{
	show_func(__func__, MY_START, NULL);
	char	*tmp;

	while (tk)
	{
		tmp = tk->content;
		tk->content = ft_strtrim(tmp, " \t\v\r\n\f");
		free(tmp);
		tk = tk->next;
	}
	return ;
}

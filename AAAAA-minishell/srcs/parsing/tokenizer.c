/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 14:54:35 by sgoffaux          #+#    #+#             */
/*   Updated: 2023/11/29 19:42:00 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	copy_in_quotes(char *start, char *end, char **str, int *i)
{
	while (start != end)
	{
		(*str)[*i] = *start;
		start++;
		(*i)++;
	}
}

/*
treat_quotes(char **str):
	This function advances the given pointer to the next character that it is on.
	For example, if the function is called with the pointer pointing at a quotation
	mark, it will advance the pointer in the string to the next occurence of that
	same quotation mark. The function returns 0 if this character is never met,
	which would signify an unclosed quotation mark.
*/
static int	treat_quotes(char **str)
{
	char	open_quote;

	open_quote = **str;
	++(*str);
	while (**str && **str != open_quote)
		++(*str);
	if (!**str || (**str != open_quote))
		return (0);
	return (1);
}

static char	*end_remove_quotes(char *tmp, char *copy, int i)
{
	char	*ret;

	tmp[i] = '\0';
	ret = ft_strdup(tmp);
	free(tmp);
	free(copy);
	return (ret);
}

/*
remove_quotes(char *str):
	This function removes any redundant quotation marks
*/
char	*remove_quotes(char *str)
{
	char	*tmp;
	char	*copy;
	char	*start;
	int		i;

	i = 0;
	copy = str;
	tmp = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!tmp)
		return (NULL);
	while (str && *str)
	{
		if (*str == '\"' || *str == '\'')
		{
			start = str + 1;
			treat_quotes(&str);
			copy_in_quotes(start, str, &tmp, &i);
		}
		else
			tmp[i++] = *str;
		str++;
	}
	return (end_remove_quotes(tmp, copy, i));
}

/*
token_setter(char *str, t_token **head):
	This function iterates over the line buffer read by readline and
	splits it into tokens based on the operations it encounters.
*/
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
			if (curr.type != TOKEN_EAT)
				add_token(head, create_token(curr.op, curr.size, curr.type));
			prev = str;
		}
		else if ((*str == '\"' || *str == '\'') && !treat_quotes(&str))
			return (0);
		else
			++str;
	}
	if (prev != str)
		add_token(head, create_token(prev, str - prev, TOKEN_NAME));
	return (1);
}

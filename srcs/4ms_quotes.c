/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4ms_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:10:37 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/30 19:30:50 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/// @brief 		check if estring enclosing quotes are single or double
/// @param str	string to check
/// @return		1 if single quotes (' '), 0 if double quotes (" ")
///				MISLEADING CHANGE STATUS
static int	first_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i] && !(str[i] == '\'' || str[i] == '\"'))
		i++;
	if (str[i] == '\'')
		return (1);
	return (0);
}

/// @brief 		Check if the #quotation marks before index is odd or even.
/// @param str	string to check
/// @param i	termination index
/// @param c	quotation mark to check
/// @return		1 if #quotation before index i is odd, 0 if even
///				MISLEADING CHANGE STATUS
int	odd_before(char **str, int i, char c)
{
	int	count;
	int	j;

	count = 0;
	while (i--)
	{
		j = 0;
		while (str[i] && str[i][j])
		{
			if (str[i][j] == c)
				count++;
			j++;
		}
	}
	return (count % 2);
}

/// @brief 		Check if the #quotation marks after index is odd or even.
/// @param str	string to check
/// @param i	termination index
/// @param c	quotation mark to check
/// @return		1 if is odd, 0 if even
///				MISLEADING CHANGE STATUS
int	odd_after(char **str, int i, char c)
{
	int	count;
	int	j;

	count = 0;
	while (str[i])
	{
		j = 0;
		while (str[i] && str[i][j])
		{
			if (str[i][j] == c)
				count++;
			j++;
		}
		i++;
	}
	return (count % 2);
}

void	copy_in_quotes(char *start, char *end, char **str, int *i)
{
	while (start != end)
	{
		(*str)[*i] = *start;
		start++;
		(*i)++;
	}
}

/// @brief 		advances the given pointer to the next character that it is on
///				For example, if the function is called with the pointer pointing
///				at a quotation mark, it will advance the pointer in the string
///				to the next occurence of that same quotation mark. The function
///				returns 0 if this character is never met, which would signify
///				an unclosed quotation mark.
/// @param str	string to advance
/// @return		0 if unclosed quotation mark (error), 1 otherwise (success)
///				MISLEADING CHANGE STATUS
int	treat_quotes(char **str)
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

/// @brief 		cleanup after removing redundant quotes and frees up alloc
/// @param tmp	string to clean up
/// @param copy	string to clean up
/// @param i	termination index
/// @return		resulting cleanded string
char	*end_remove_quotes(char *tmp, char *copy, int i)
{
	char	*ret;

	tmp[i] = '\0';
	ret = ft_strdup(tmp);
	free(tmp);
	free(copy);
	return (ret);
}

/// @brief 		removes redundant quotes
/// @param str	string to remove quotes
/// @return		string clean of quotes
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


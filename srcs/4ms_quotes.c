/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4ms_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:10:37 by antoda-s          #+#    #+#             */
/*   Updated: 2023/12/04 23:36:11 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/// @brief 		check if estring enclosing quotes are single or double
/// @param str	string to check
/// @return		1 if single quotes (' '), 0 if double quotes (" ")
///				MISLEADING CHANGE STATUS
int	first_quote(char *str)
{
	int	i;

	show_func(__func__, MY_START);
	i = 0;
	while (str[i] && !(str[i] == '\'' || str[i] == '\"'))
		i++;
	if (str[i] == '\'')
		return (1);
	show_func(__func__, SUCCESS);
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

	show_func(__func__, MY_START);
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
	show_func(__func__, SUCCESS);
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

	show_func(__func__, MY_START);
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
	show_func(__func__, SUCCESS);
	return (count % 2);
}

/// @brief 			Copies string contents between quotes
/// @param start 	Pointer at start quote
/// @param end 		pointer at end quote
/// @param str 		destination string
/// @param i 		destination index ?? NEEDS REFACTOR with LIBFT
void	copy_in_quotes(char *start, char *end, char **str, int *i)
{
	show_func(__func__, MY_START);
	while (start != end)
	{
		(*str)[*i] = *start;
		start++;
		(*i)++;
	}
	show_func(__func__, SUCCESS);
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

	show_func(__func__, MY_START);
	open_quote = **str;
	++(*str);
	while (**str && **str != open_quote)
		++(*str);
	if (!**str || (**str != open_quote))
		return (0);
	show_func(__func__, SUCCESS);
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

	show_func(__func__, MY_START);
	tmp[i] = '\0';
	ret = ft_strdup(tmp);
	ft_free(tmp);
	ft_free(copy);
	show_func(__func__, SUCCESS);
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

	show_func(__func__, MY_START);
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
	show_func(__func__, SUCCESS);
	return (end_remove_quotes(tmp, copy, i));
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5ms_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 19:00:01 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/30 21:52:28 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/// @brief 		This function gets the environment variable name after a $ and
///				returns its corresponding value in the environment.
/// @param str	String to be parsed
/// @param envp	Environment variables
/// @param i	Index start
/// @return		replace variable
static char	*replace_loop(char *str, char **envp, int *i)
{
	char	*tmp;
	char	c;

	if (str[0] == '?')
	{
		(*i)++;
		if (g_exit_status >= 256)
			return (ft_itoa(WEXITSTATUS(g_exit_status)));
		else
			return (ft_itoa(g_exit_status));
	}
	if (ft_isspace(str[0]) || str[0] == '\'' || str[0] == '\"')
		return (ft_strdup("$"));
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	c = str[*i];
	str[*i] = '\0';
	tmp = get_env_content(str, envp); // envp_getter.c
	str[*i] = c;
	return (tmp);
}

/// @brief 			Splits the string on '$' and accounts for the possibility
///					that the string may begin with a '$'
/// @param line_buf	String to be split
/// @param before	Pointer to the string before the first '$'
/// @param i		Index start
/// @return			Split string
static char	**init_split_before(char *line_buf, char **before, int *i)
{
	char	**split;

	split = ft_split(line_buf, '$');
	if (line_buf[0] && line_buf[0] != '$')
	{
		*before = ft_strdup(split[0]);
		(*i)++;
	}
	else
		*before = ft_strdup("");
	return (split);
}

/// @brief 				Replaces ARGS in a given string by the environment vars
///						by iterating through the string and replacing each
///						environment variable with its value.
/// @param line_buf		String to be parsed
/// @param envp			Environment variables
/// @param i			Index start
/// @param j			Index end
/// @return				String with ARGS replaced by envp vars
char	*replace_env_var(char *line_buf, char **envp, int i, int j)
{
	char	**split;
	char	*before;
	char	*tmp;

	before = NULL;
	split = init_split_before(line_buf, &before, &i);
	while (split[i])
	{
		if ((odd_before(split, i, '\'') && odd_after(split, i, '\''))
			&& (first_quote(line_buf) || !(odd_before(split, i, '\"')
					&& odd_after(split, i, '\"'))))
			before = ft_strjoin_free(before, ft_strjoin("$", split[i]));
		else
		{
			j = 0;
			tmp = ft_strjoin_free(before, replace_loop(split[i], envp, &j));
			before = ft_strjoin(tmp, split[i] + j);
			free(tmp);
		}
		i++;
	}
	if (line_buf[ft_strlen(line_buf) - 1] == '$')
		before = ft_strjoin_free(before, ft_strdup("$"));
	free_split(split);
	return (before);
}

/// @brief		This function replaces multiple spaces with a single space
/// @param str	String to be parsed
/// @return		String with multiple spaces replaced by a single space
static char	*replace_multiple_space(char *str)
{
	char	**split;
	char	*tmp;
	int		i;

	i = 0;
	split = ft_split_set(str, " \t\v\r\f\n");
	tmp = malloc(sizeof(char) * ft_strlen(str));
	if (!tmp)
		return (str);
	while (split[i])
	{
		if (i > 0)
			tmp = ft_strjoin_free(tmp, ft_strdup(" "));
		tmp = ft_strjoin_free(tmp, split[i]);
		i++;
	}
	free(split);
	free(str);
	return (tmp);
}

/// @brief		This function iterates over the environment variables to
///				find whether or not the given variable (str) is defined and
///				returns the content or an empty freeable string.
/// @param str	Variable to be found
/// @param envp	Environment variables
/// @return		Content of the variable
char	*get_env_content(char *str, char **envp)
{
	char	*tmp;
	char	*ret;
	int		len;

	tmp = ft_strjoin(str, "=");
	len = ft_strlen(tmp);
	ret = NULL;
	while (*envp)
	{
		if (!ft_strncmp(tmp, *envp, len))
		{
			ret = ft_strdup(*envp + len);
			break ;
		}
		envp++;
	}
	free(tmp);
	if (!ret)
	{
		ret = ft_strdup("");
		if (!ret)
			return (NULL);
	}
	return (replace_multiple_space(ret));
}



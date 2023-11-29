/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 16:15:17 by sgoffaux          #+#    #+#             */
/*   Updated: 2021/10/07 16:34:28 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
first_quote(char *str):
	This function returns 1 if the outer quotation marks around a point in a 
	string are single quotes and returns 0 otherwise.
*/
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

/*
replace_loop(char *str, char **envp, int *i):
	This function gets the environment variable name after a $ and returns its
	corresponding value in the environment.
*/
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
	tmp = get_env_content(str, envp);
	str[*i] = c;
	return (tmp);
}

/*
init_split_before(char *line_buf, char **before, int *i):
	This function splits our given line buffer on '$' and accounts for the 
	possibility that the string may begin with a '$'.
*/
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

/*
replace_env_var(char *line_buf, char **envp, int i, int j):
	This function splits our given line buffer into one or more environment 
	variables, determines whether or not they need to be replaced based on 
	the quotation marks that surround each one, and rebuilds the line buffer 
	with these replacements and returns the new string.
*/
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

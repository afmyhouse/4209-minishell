/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 16:28:57 by mdeclerf          #+#    #+#             */
/*   Updated: 2021/10/07 17:02:02 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*add_forw_slash(char *str)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strdup(str);
	free(str);
	str = (char *)malloc(sizeof(char) * (ft_strlen(tmp) + 2));
	if (!str)
		return (NULL);
	while (tmp[i])
	{
		str[i] = tmp[i];
		i++;
	}
	str[i++] = '/';
	str[i] = '\0';
	free(tmp);
	return (str);
}

static int	check_path_line(char **env)
{
	int	i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	return (i);
}

static char	**path_fill(char **env, int p_line)
{
	char	**path;
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 5;
	path = ft_split(env[p_line], ':');
	tmp = ft_strdup(path[0] + 5);
	free(path[0]);
	path[0] = tmp;
	i = 0;
	while (path[i])
	{
		tmp = ft_strdup(path[i]);
		free(path[i]);
		path[i] = add_forw_slash(tmp);
		i++;
	}
	return (path);
}

/*
split_paths(char **env) :
	This function creates a char ** with every possible path listed
	in the PATH var in envp.
*/
char	**split_paths(char **env)
{
	char	**path;
	int		p_line;

	p_line = check_path_line(env);
	if (env[p_line] != NULL)
		path = path_fill(env, p_line);
	else
	{
		path = malloc(sizeof(char *));
		if (!path)
			return (NULL);
		path[0] = NULL;
	}
	return (path);
}

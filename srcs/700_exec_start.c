/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   700_exec_start.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 00:26:42 by antoda-s          #+#    #+#             */
/*   Updated: 2024/02/10 00:40:41 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_forw_slash(char *str)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strdup(str);
	free(str);
	str = (char *)malloc(sizeof(char) * (ft_strlen(tmp) + 2));
	if (!str)
	{
		return (NULL);
	}
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

char	**path_fill(char **env, int p_line)
{
	char	**path;
	char	*tmp;
	int		i;

	i = 0;
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

char	**split_paths(char **env)
{
	char	**path;
	int		i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;

	if (env[i] != NULL)
		path = path_fill(env, i);
	else
	{
		path = malloc(sizeof(char *));
		if (!path)
			return (NULL);
		path[0] = NULL;
	}
	return (path);
}

/// @brief 			Executes the command
/// @param s 		Script contents and parameters including redirect info
/// @return 		SUCCESS or ERROR
int execute(t_script *s)
{
	//show_func(__func__, MY_START, NULL);
	char	**path;

	execute_show(s);
	path = split_paths(s->envp);
	if (s->cmd_count == 1)
	{
		if (exec_one(s, path))
			return (1);
	}
	else if (exec_many(s, path))
		return (1);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &s->termios_p);
	//show_func(__func__, SUCCESS, NULL);
	//show_array(s->envp);
	return (0);
}


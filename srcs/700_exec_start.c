/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   700_exec_start.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 00:26:42 by antoda-s          #+#    #+#             */
/*   Updated: 2024/03/12 18:25:08 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_path_index(char **envp)
{
	show_func(__func__, MY_START, NULL);
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

char	**split_path(char **envp)
{
	show_func(__func__, MY_START, NULL);
	int		i;
	char	**path;
	char	*tmp;

	i = get_path_index(envp);
	if (i == -1)
		return (NULL);
	tmp = ft_strdup(envp[i] + 5);
	path = ft_split(tmp, ':');
	ft_free(tmp);
	i = -1;
	while (path[++i])
	{
		path[i] = ft_strjoin_free(path[i], ft_strdup("/"));
	}
	return (path);
}

/// @brief 			Executes the command
/// @param s 		Script contents and parameters including redirect info
/// @return 		SUCCESS or ERROR
int	execute(t_script *s)
{
	char	**path;
	show_func(__func__, MY_START, NULL);


	execute_show(s);
	path = split_path(s->envp);
	if (s->cmd_count == 1)
	{
		if (exec_one(s, path))
			return (ERROR);
	}
	else if (exec_many(s, path))
		return (ERROR);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &s->termios_p);
	return (SUCCESS);
}

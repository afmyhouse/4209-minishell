/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   700_exec_start.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 00:26:42 by antoda-s          #+#    #+#             */
/*   Updated: 2024/02/15 20:05:40 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_path_index(char **envp)
{
	// show_func(__func__, MY_START, NULL);
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			// show_func(__func__, SUCCESS, ft_strjoin("PATH index = ", ft_itoa(i)));
			return (i);
		}
		i++;
	}
	// show_func(__func__, ERROR, NULL);
	return (-1);
}

char	**split_path(char **envp)
{
	// show_func(__func__, MY_START, NULL);
	int		i;
	char	**path;

	i = get_path_index(envp);
	if (i == -1)
		return (NULL);
	path = ft_split(envp[i] + 5, ':');

	i = -1;
	while (path[++i])
	{
		path[i] = ft_strjoin(path[i], "/");
		//show_func(__func__, SHOW_MSG, path[i]);
	}
	// show_array(path, "path");
	// show_func(__func__, SUCCESS, NULL);
	return (path);
}

/// @brief 			Executes the command
/// @param s 		Script contents and parameters including redirect info
/// @return 		SUCCESS or ERROR
int execute(t_script *s)
{
	show_func(__func__, MY_START, NULL);
	char	**path;

	execute_show(s);
	path = split_path(s->envp);
	if (s->cmd_count == 1)
	{
		if (exec_one(s, path))
			return (ERROR); // estava return (1) filipe 20fev
	}
	else if (exec_many(s, path))
		return (ERROR); // estava return (1) filipe 20fev
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &s->termios_p);
	show_func(__func__, SUCCESS, NULL);
	return (SUCCESS);
}


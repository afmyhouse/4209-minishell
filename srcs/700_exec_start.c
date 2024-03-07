/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   700_exec_start.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 00:26:42 by antoda-s          #+#    #+#             */
/*   Updated: 2024/03/05 20:12:47 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_path_index(char **envp)
{
	show_pointer(__func__, MY_START, "SHOW envp", envp);
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
	char *tmp;

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
		//show_func(__func__, SHOW_MSG, ft_strdup(path[i]);
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
	// show_func(__func__, MY_START, NULL);
	char	**path;

	// execute_show(s);
	path = split_path(s->envp);
	// printf("%s : *************************************************** %s\n", SBHGRN, SRST);
	// show_pointer(__func__, D_MALLOC, "path", path);
	// show_pointer(__func__, SHOW_MSG, "envp", s->envp);
	// show_pointer(__func__, SHOW_MSG, "envt", s->envt);
	// printf("%s : *************************************************** %s\n", SBHGRN, SRST);
	if (s->cmd_count == 1)
	{
		if (exec_one(s, path))
			return (ERROR); // estava return (1) filipe 20fev
	}
	else if (exec_many(s, path))
		return (ERROR); // estava return (1) filipe 20fev
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &s->termios_p);
	// show_func(__func__, SUCCESS, NULL);
	return (SUCCESS);
}


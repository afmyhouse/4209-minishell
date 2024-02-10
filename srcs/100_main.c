/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   100_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 19:27:05 by antoda-s          #+#    #+#             */
/*   Updated: 2024/02/09 23:47:21 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

/// @brief 		Creates array from system environment variables
/// @param envp system environment variables from main (... char **envp)
/// @return 	array copy of system environment variables
char	**envp_init(char **envp)
{
	char	**ms_envp;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	ms_envp = malloc(sizeof(char *) * (i + 1));
	if (!ms_envp)
	{
		return (NULL);
	}
	i = 0;
	while (envp[i])
	{
		ms_envp[i] = ft_strdup(envp[i]);
		if (!ms_envp[i])
			return (NULL);
		i++;
	}
	ms_envp[i] = NULL;
	return (ms_envp);
}

/// @brief 		Initialize basic int
/// @param s 	struct with pparams to initialize
void	struct_init(t_script *s)
{
		s->cmd_count = 0;
		s->exit_status = 0;
		s->fd[0] = STDIN_FILENO;
		s->fd[1] = STDOUT_FILENO;
}

/// @brief 				Initializes the shell and keeps looping until exit
/// @param script		Script structure (see minishell struct)
/// @return				void
int	ms_loop(t_script *s)
{
	int		status;
	char	*line_buffer;

	line_buffer = NULL;
	while (1)
	{
		struct_init(s);
		signal_setter();
		status = parser(s, &line_buffer);
		ft_free_arr(&line_buffer);
		if (status == 1)
			continue ;
		else if (status == 2)
		{
			ft_putendl_fd("exit", 2);
			break ;
		}
		if (s->cmd_count > 0)
			if (execute(s))
				break ;
		free_commands(s->cmds, s->cmd_count);
	}
	if (s->cmd_count > 0)
		free_commands(s->cmds, s->cmd_count);
	return (0);
}

/// @brief 			Main function MINISHELL
/// @param argc		Number of arguments (NOT USED)
/// @param argv		Arguments (NOT USED)
/// @param envp		Environment variables
/// @return
int	main(int argc, char **argv, char **envp)
{
	t_script	s;

	(void)argc;
	(void)argv;
	s.envp = envp_init(envp);
	s.envt = NULL;
	termios_getter(&s.termios_p);
	ms_loop(&s);
	free_array(s.envp);
	return (0);
}

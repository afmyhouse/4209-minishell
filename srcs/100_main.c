/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   100_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 19:27:05 by antoda-s          #+#    #+#             */
/*   Updated: 2024/03/22 21:52:34 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

void	update_shlvl(t_script *s)
{
	char	*shlvl;
	char	*new_shlvl;
	int		i;

	shlvl = env_var_getter("MSHLVL", s->envp, NULL);
	if (!shlvl)
	{
		env_var_setter("1", "MSHLVL", &s->envp);
		return ;
	}
	i = ft_atoi(shlvl);
	new_shlvl = ft_itoa(i + 1);
	if (!new_shlvl)
	{
		return_error("", errno, 1);
		return ;
	}
	env_var_setter(new_shlvl, "MSHLVL", &s->envp);
	show_func(__func__, SUCCESS, "MSHLVL", "READY");
	ft_free(shlvl);
	ft_free(new_shlvl);
}

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
	ms_envp = ft_calloc(i + 1, sizeof(char *));
	if (!ms_envp)
	{
		return_error("", errno, 1);
		return (NULL);
	}
	i = -1;
	while (envp[++i])
	{
		ms_envp[i] = ft_strdup(envp[i]);
		if (!ms_envp[i])
		{
			return_error("", errno, 1);
			return (NULL);
		}
	}
	ms_envp[i] = NULL;
	return (ms_envp);
}

/// @brief 		Initialize basic int
/// @param s 	struct with pparams to initialize
void	struct_init(t_script *s)
{
	s->path = NULL;
	s->hd = NULL;
	s->cmd_count = 0;
	s->exit_status = 0;
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
		ft_free(line_buffer);
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
	update_shlvl(&s);
	s.envt = ft_calloc(1, sizeof(char *));
	if (!s.envt)
	{
		return_error("", errno, 1);
		return (1);
	}
	s.envt[0] = NULL;
	termios_getter(&s.termios_p);
	s.home = env_var_getter("HOME", s.envp, NULL);
	ms_loop(&s);
	return (free_array(s.envp, 0));
}

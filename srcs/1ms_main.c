/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1ms_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 19:27:05 by antoda-s          #+#    #+#             */
/*   Updated: 2023/12/04 10:57:04 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/// @brief 		Creates array from system environment variables
/// @param envp system environment variables from main (... char **envp)
/// @return 	array copy of system environment variables
char	**envp_getter(char **envp)
{
	char	**ms_envp;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	ms_envp = malloc(sizeof(char *) * (i + 1));
	if (!ms_envp)
		return (NULL);
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

/// @brief 				Gets the terminal settings
/// @param termios_p	Pointer to the termios settings structure
void	termios_getter(struct termios *termios_p)
{
	if (tcgetattr(STDIN_FILENO, termios_p) != 0)
		perror("tcgetattr() error");
	else
	{
		if (termios_p->c_iflag & BRKINT)
			ft_putstr("BRKINT is set");
		else
			ft_putstr("BRKINT is not set");
		if (termios_p->c_cflag & PARODD)
			ft_putstr("Odd parity is used");
		else
			puts("Even parity is used");
		if (termios_p->c_lflag & ECHO)
			ft_putstr("ECHO is set");
		else
			ft_putstr("ECHO is not set");
		printf("The end-of-file character is x'%02x'\n", termios_p->c_cc[VEOF]);
	}
}

/// @brief 				Initializes the shell and keeps looping until exit
/// @param script		Script structure (see minishell struct)
/// @param line_buffer	Line buffer
/// @return				void
int	ms_loop(t_script *script, char **line_buffer)
{
	int	result;

	while (1)
	{
		script->cmd_count = 0;
		sig_setter();
		result = parser(script, line_buffer);
		free(line_buffer);
		if (result == 1)
			continue ;
		else if (result == 2)
		{
			ft_putendl_fd("exit", 2);
			break ;
		}
		if (script->cmd_count > 0)
		{
			if (execute(script))
				break ;
		}
		free_commands(script->commands, script->cmd_count);
	}
	if (script->cmd_count > 0)
		free_commands(script->commands, script->cmd_count);
	return (0);
}

/// @brief 			Main function MINISHELL
/// @param argc		Number of arguments (NOT USED)
/// @param argv		Arguments (NOT USED)
/// @param envp		Environment variables
/// @return
int	main(int argc, char **argv, char **envp)
{
	t_script	script;
	char		*line_buffer;

	line_buffer = NULL;
	(void)argc;
	(void)argv;
	script.envp = envp_getter(envp);
	termios_getter(&script.termios_p);
	ms_loop(&script, &line_buffer);
	free_envp(script.envp);

	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1ms_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 19:27:05 by antoda-s          #+#    #+#             */
/*   Updated: 2023/12/05 00:00:13 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_exit_status;

/// @brief 		Creates array from system environment variables
/// @param envp system environment variables from main (... char **envp)
/// @return 	array copy of system environment variables
char	**envp_getter(char **envp)
{
	char	**ms_envp;
	int		i;

	show_func(__func__, MY_START);
	i = 0;
	while (envp[i])
		i++;
	ms_envp = malloc(sizeof(char *) * (i + 1));
	if (!ms_envp)
	{
		show_func(__func__, ERROR);
		return (NULL);
	}
	i = 0;
	while (envp[i])
	{
		ms_envp[i] = ft_strdup(envp[i]);
		if (!ms_envp[i])
		{
			show_func(__func__, ERROR);
			return (NULL);
		}
		i++;
	}
	ms_envp[i] = NULL;
	show_func(__func__, SUCCESS);
	return (ms_envp);
}

/// @brief 				Gets the terminal settings
/// @param termios_p	Pointer to the termios settings structure
void	termios_getter(struct termios *termios_p)
{
	show_func(__func__, MY_START);
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

	show_func(__func__, MY_START);
	while (1)
	{
		script->cmd_count = 0;
		sig_setter();
		printf("1 ***************************\n");
		result = parser(script, line_buffer);
		printf("2 ***************************\n");
		ft_free_str(line_buffer);
		printf("3 ***************************\n");
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

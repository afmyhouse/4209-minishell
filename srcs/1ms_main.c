/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1ms_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 19:27:05 by antoda-s          #+#    #+#             */
/*   Updated: 2023/12/14 14:05:20 by antoda-s         ###   ########.fr       */
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
			ft_putstr("BRKINT is set\n");
		else
			ft_putstr("BRKINT is not set\n");
		if (termios_p->c_cflag & PARODD)
			ft_putstr("Odd parity is used\n");
		else
			puts("Even parity is used\n");
		if (termios_p->c_lflag & ECHO)
			ft_putstr("ECHO is set\n");
		else
			ft_putstr("ECHO is not set\n");
		printf("The end-of-file character is x'%02x'\n", termios_p->c_cc[VEOF]);
	}
	show_func(__func__, SUCCESS);
}

void 	termios_setter(struct termios *termios_p)
{
	show_func(__func__, MY_START);
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, termios_p) != 0)
		perror("tcsetattr() error");
	else
	{
		if (termios_p->c_iflag & BRKINT)
			ft_putstr("BRKINT is set\n");
		else
			ft_putstr("BRKINT is not set\n");
		if (termios_p->c_cflag & PARODD)
			ft_putstr("Odd parity is used\n");
		else
			puts("Even parity is used\n");
		if (termios_p->c_lflag & ECHO)
			ft_putstr("ECHO is set\n");
		else
			ft_putstr("ECHO is not set\n");
		printf("The end-of-file character is x'%02x'\n", termios_p->c_cc[VEOF]);
	}
	show_func(__func__, SUCCESS);
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
		printf("%s : 1 ***************************\n", __func__);
		result = parser(script, line_buffer);
		printf("%s : 2 ***************************\n", __func__);
		ft_free_str(line_buffer);
		printf("%s : 3 ***************************\n", __func__);
		if (result == 1)
			continue ;
		else if (result == 2)
		{
			printf("%s : X ***************************\n", __func__);
			ft_putendl_fd("exit", 2);
			break ;
		}
		if (script->cmd_count > 0)
		{
			printf("%s : 4 ***************************\n", __func__);
			if (execute(script))
				break ;
		}
		free_commands(script->commands, script->cmd_count);
	}
	if (script->cmd_count > 0)
		free_commands(script->commands, script->cmd_count);
	show_func(__func__, SUCCESS);
	return (0);
}

/// @brief 			Main function MINISHELL
/// @param argc		Number of arguments (NOT USED)
/// @param argv		Arguments (NOT USED)
/// @param envp		Environment variables
/// @return
int	main(int argc, char **argv, char **envp)
{
	show_func(__func__, MY_START);
	t_script	script;
	char		*line_buffer;

	line_buffer = NULL;
	(void)argc;
	(void)argv;
	script.envp = envp_getter(envp);
	termios_getter(&script.termios_p);
	ms_loop(&script, &line_buffer);
	free_envp(script.envp);
	show_func(__func__, SUCCESS);
	return (0);
}

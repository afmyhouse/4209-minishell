/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 19:27:05 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/29 13:48:22 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**envp_getter(char **envp)
{
	char	**new_envp;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	new_envp = malloc(sizeof(char *) * (i + 1));
	if (!new_envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp[i])
			return (NULL);
		i++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}

void	minishel_signals(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}


/// @brief 				Initializes the shell and keeps looping until exit
/// @param script		Script structure (see minishell struct)
/// @param line_buffer	Line buffer
/// @return				void
int	minishell_loop(t_script *script, char **line_buffer)
{
	int	result;

	while (1)
	{
		script->cmd_count = 0;
		minishell_signals();
		result = parse(script, line_buffer);
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
	script.envp = envpgetter(envp);
	tcgetattr(STDIN_FILENO, &script.termios_p);
	minishel_loop(&script, &line_buffer);
	free_envp(script.envp);

	return (0);
}

// void continue_main_here(void)
// {
// 	//	init_shell();
// 	while (1)
// 	{
// 		printf("%s", prompt);
// 		lineptr = readline(lineptr);
// 		if (lineptr == NULL)
// 		{
// 			printf("Exiting shell...\n");
// 			free ((char *)lineptr);
// 			return (-1);
// 		}
// 		else if (ft_strncmp(lineptr, exit_shell, ft_strlen(exit_shell)) == 0) //tratamento temporario do exit, ja que exit é um command a ser executado e nao
// 		{
// 			printf("Exiting shell...\n");
// 			free ((char *)lineptr);
// 			return (-1);
// 		}
// 		while(lineptr != NULL)
// 		{
// 			lineptr = ft_tokenize(lineptr, &nbr_tokens);
// 		}
// 	}
// 	free((char *)lineptr);
// 	free((char *) exit_shell);
// 	return (0);
// }

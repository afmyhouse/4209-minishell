/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 13:26:41 by sgoffaux          #+#    #+#             */
/*   Updated: 2023/11/29 13:44:29 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**envp_malloc(char **envp)
{
	char	**tmp;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	tmp = malloc(sizeof(char *) * (i + 1));
	if (!tmp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		tmp[i] = ft_strdup(envp[i]);
		i++;
	}
	tmp[i] = NULL;
	return (tmp);
}

static void	main_loop(t_script *script, char **line_buf)
{
	int	ret;

	while (1)
	{
		script->cmd_count = 0;
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, SIG_IGN);
		ret = parse(script, line_buf);
		free(*line_buf);
		if (ret == 1)
			continue ;
		else if (ret == 2)
		{
			ft_putendl_fd("exit", 2);
			break ;
		}
		if (script->cmd_count > 0)
		{
			if (handle_cmd(script))
				break ;
		}
		free_commands(script->commands, script->cmd_count);
	}
	if (script->cmd_count > 0)
		free_commands(script->commands, script->cmd_count);
}

int	main(int argc, char **argv, char **envp)
{
	t_script	script;
	char		*line_buf;

	(void)argc;
	(void)argv;
	script.envp = envp_malloc(envp);
	line_buf = NULL;
	tcgetattr(STDIN_FILENO, &script.termios_p);
	main_loop(&script, &line_buf);
	free_path_env(script.envp);
	return (g_exit_status);
}

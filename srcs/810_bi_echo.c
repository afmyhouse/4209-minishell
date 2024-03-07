/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   810_bi_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:43:00 by antoda-s          #+#    #+#             */
/*   Updated: 2024/03/02 01:13:53 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief  		Checks if the echo command has the flag '-n'
/// @param str 		Argument string
/// @return 		1 if true, 0 if false
int	bi_echo_flag(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-')
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

/// @brief 			Builtin echo command
/// @param command	Builtin command arguments
/// @return			SUCCESS if success, ERROR if error
//int	bi_echo(t_command cmds)
int	bi_echo(t_script *s, int n)
{
	// show_func(__func__, MY_START, ft_strjoin("bi: ", s->cmds[n].argv[0]));
	int		i;
	char	term;

	i = 1;
	term = '\n';
	while (s->cmds[n].argv[i] && bi_echo_flag(s->cmds[n].argv[i]))
	{
		term = '\0';
		i++;
	}
	while (s->cmds[n].argv[i])
	{
		ft_putstr_fd(s->cmds[n].argv[i], STDOUT_FILENO);
		i++;
		if (s->cmds[n].argv[i] && s->cmds[n].argv[i - 1][0] != '\0')
			write (STDOUT_FILENO, " ", 1);
	}
	ft_putchar_fd(term, STDOUT_FILENO);
	// show_func(__func__, SUCCESS, NULL);
	return (SUCCESS);
}

/// @brief 			Builtin echo command env var '_' update (last cmd)
/// @param s		Parsed script with command(s) to execute
/// @param n		Index of cmd to executes
/// @return			SUCCESS if success, ERROR if error
int	bi_env_upd(t_script *s, int n)
{
	// show_func(__func__, MY_START, NULL);
	int i;

	i = s->cmds[n].argc - 1;
	while (!ft_strncmp(s->cmds[n].argv[i], "", 1) && i > 0)
		i--;
	env_var_setter(s->cmds[n].argv[i],"_", &s->envp);
	// show_func(__func__, SUCCESS, NULL);
	return (SUCCESS);
}

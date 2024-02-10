/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   870_bi_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 00:10:23 by antoda-s          #+#    #+#             */
/*   Updated: 2024/02/10 00:10:47 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief 			Builtin 'exit' command argument checker
/// @param str		Builtin 'exit' argument string
/// @return			SUCSESS or ERROR
int	ft_is_str_digit(char *str)
{
	int	i;

	//show_func(__func__, MY_START, NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57)
		{
			//show_func(__func__, ERROR, NULL);
			return (ERROR);
		}
		i++;
	}
	//show_func(__func__, SUCCESS, NULL);
	return (SUCCESS);
}

/// @brief 			Shows error and program sourcing it
/// @param msg		Message to show
/// @param system	Shows system error if true
/// @return			SUCCESS
int	exit_error_args(const char *msg, int system)
{
	//show_func(__func__, MY_START, NULL);

	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("Minishell: exit: ", 2);
	ft_putstr_fd(msg, 2);
	errno = system;
	//show_func(__func__, SUCCESS, NULL);
	return (system);
}

int	exit_error_notnum(const char *msg, int system)
{
	//show_func(__func__, MY_START, NULL);

	ft_putstr_fd("Minishell: exit: '", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("':  numeric argument required\n", 2);
	errno = system;
	//show_func(__func__, SUCCESS, NULL);
	return (system);
}

/// @brief 			Builtin exit command
/// @param args		Builtin command arguments
/// @return			exit status or ERROR
int	bi_exit(t_script *s, int n)
{
	//show_func(__func__, MY_START, NULL);

	env_var_setter("minishell", "_", &s->envp);
	if (s->cmds[n].argc == 1)
		exit (0);
	if (s->cmds[n].argc > 2)
	{
		return (exit_error_args("too many arguments\n", 2));
	}
	if (ft_is_str_digit(s->cmds[n].argv[1]) == 1)
	{
		//show_func(__func__, ERROR, NULL);
		exit_error_notnum(s->cmds[n].argv[1], 2);
		free_commands(s->cmds, s->cmd_count);
		free_array(s->envp);
		exit (2);
	}
	//show_func(__func__, SUCCESS, NULL);
	exit (ft_atoi(s->cmds[n].argv[1]));
}

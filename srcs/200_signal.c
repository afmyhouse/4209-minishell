/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   200_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:38:24 by antoda-s          #+#    #+#             */
/*   Updated: 2024/03/14 18:36:08 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief		Signal processing functions setter
/// @param		No parameter required
void	signal_setter(void)
{
	show_func(__func__, MY_START, NULL);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

/// @brief		Signal processing functions setter for loop
/// @param		No parameter required
void	signal_setter_loop(void)
{
	show_func(__func__, MY_START, NULL);
	signal(SIGINT, sig_handler_fork);
	signal(SIGQUIT, sig_handler_fork);
}

/// @brief 			Handles signal SIGINT (Ctrl+C) and SIGQUIT (Ctrl+\)
///					Instead of exiting, the sig handler provides a new line
/// @param signum	The signal number
/// @return			void
void	sig_handler(int signum)
{
	show_func(__func__, MY_START, NULL);
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		g_exit_status = 130;
	}
}

/// @brief 			Handles signal SIGINT (Ctrl+C) and SIGQUIT (Ctrl+\)
///					Instead of exiting, the sig handler provides a new line
/// @param signum	The signal number
/// @return			void
void	sig_handler_fork(int signum)
{
	show_func(__func__, MY_START, NULL);
	if (signum == SIGQUIT)
	{
		write(1, "Quit\n", 5);
		//g_exit_status = 131;
		rl_on_new_line();
		g_exit_status = 131;
		write(1, "\r", 1);
	}
	else if (signum == SIGINT)
	{
		write(1, "\n", 1);
		// g_exit_status = 130;
		rl_on_new_line();
		g_exit_status = 130;
	}
}

/// @brief 			Handles the signal SIGINT (Ctrl + C) when in heredoc
///					Exits with status 130 : Command terminated by user
/// @param signum	The signal number
/// @return			void
void	sig_handler_heredoc(int signum)
{
	show_func(__func__, MY_START, NULL);
	if (signum == SIGINT)
		exit(130);
}

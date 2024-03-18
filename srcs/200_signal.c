/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   200_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:38:24 by antoda-s          #+#    #+#             */
/*   Updated: 2024/03/18 23:03:26 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief		Signal processing functions setter
/// @param		No parameter required
// void	signal_setter_parent(void)
// {
// 	show_func(__func__, MY_START, NULL);
// 	// signal(SIGINT, SIG_IGN);
// 	// signal(SIGQUIT, SIG_IGN);
// 	signal(SIGINT, sig_handler_parent);
// 	signal(SIGQUIT, sig_handler_parent);
// }

// void signal_selector(t_script *s)
// {
// 	char *mshlvl;

// 	mshlvl = env_var_getter("MSHLVL", s->envp, NULL);
// 	s->mshlvl = ft_atoi(mshlvl);
// 	if (s->mshlvl > 1)
// 		signal_setter_fork();
// 	else
// 		signal_setter();
// 	ft_free (mshlvl);
// 	return ;
// }

/// @brief		Signal processing functions setter
/// @param		No parameter required
void	signal_setter(void)
{
	show_func(__func__, MY_START, NULL);
	// printf("%s : \n", __func__);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

/// @brief		Signal processing functions setter for loop
/// @param		No parameter required
void	signal_setter_fork(void)
{
	show_func(__func__, MY_START, NULL);
	// printf("%s : \n", __func__);
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
	// printf("%s : pid = %d\n", __func__, getpid());
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		g_exit_status = 130;
	}
	// printf("%s : g exit status = %d\n", __func__, g_exit_status);
}

/// @brief 			Handles signal SIGINT (Ctrl+C) and SIGQUIT (Ctrl+\)
///					Instead of exiting, the sig handler provides a new line
/// @param signum	The signal number
/// @return			void
void	sig_handler_fork(int signum)
{
	show_func(__func__, MY_START, NULL);
	// printf("%s : pid = %d\n", __func__, getpid());
	if (signum == SIGQUIT)
	{
		write(2, "Quit\n", 5);
		rl_on_new_line();
		//rl_redisplay();
		//write(1, "\r", 1);
		//rl_on_new_line();
		g_exit_status = 131;
	}
	else if (signum == SIGINT)
	{
		//write(1, "\n", 1);
		// rl_replace_line("", 0);
		rl_on_new_line();
		// rl_redisplay();
		g_exit_status = 130;
	}
	// printf("%s : g exit status = %d\n", __func__, g_exit_status);
}

// void	sig_handler_parent(int signum)
// {
// 	show_func(__func__, MY_START, NULL);
// 	// printf("%s : pid = %d\n", __func__, getpid());
// 	if (signum == SIGQUIT)
// 	{
// 		write(1, "Quit\n", 5);
// 		rl_on_new_line();
// 		write(1, "\r", 1);
// 		// write(1, "\n", 1);
// 		g_exit_status = 131;
// 	}
// 	else if (signum == SIGINT)
// 	{
// 		write(1, "\n", 1);
// 		rl_replace_line("", 0);
// 		rl_on_new_line();
// 		rl_redisplay();
// 		g_exit_status = 130;
// 	}
// 	// printf("%s : g exit status = %d\n", __func__, g_exit_status);
// }

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

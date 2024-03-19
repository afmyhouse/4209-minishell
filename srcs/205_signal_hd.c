/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   205_signal_hd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:38:24 by antoda-s          #+#    #+#             */
/*   Updated: 2024/03/19 18:34:07 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief		Signal processing functions setter
/// @param		No parameter required
void	signal_setter_heredoc(t_script *s)
{
	sig_handler_heredoc(-1, s);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, (void *)sig_handler_heredoc);
}

/// @brief 			Handles the signal SIGINT (Ctrl + C) when in heredoc
///					Exits with status 130 : Command terminated by user
/// @param signum	The signal number
/// @return			void
void	sig_handler_heredoc(int signum, t_script *s)
{
	static t_script	*tmp;

	if (signum == -1)
		tmp = s;
	else if (signum == SIGINT)
		exit(free_exit(tmp, 130));
}

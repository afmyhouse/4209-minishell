/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   400_termios.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 19:27:05 by antoda-s          #+#    #+#             */
/*   Updated: 2024/04/04 00:50:27 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief 				Gets the terminal settings
/// @param termios_p	Pointer to the termios settings structure
void	termios_getter(struct termios *termios_p)
{
	show_func(__func__, FSTART, NULL);
	int	err;

	err = tcgetattr(STDIN_FILENO, termios_p);
	if (err != 0)
		error_return("tcgetattr() error", err, 1);
}

/// @brief 				Sets the terminal settings from previous "getter"
/// @param termios_p	Pointer to the termios settings structure
void	termios_setter(struct termios *termios_p)
{
	show_func(__func__, FSTART, NULL);
	int	err;

	err = tcsetattr(STDIN_FILENO, TCSAFLUSH, termios_p);
	if (err != 0)
		error_return("tcsetattr() error", err, 1);
}

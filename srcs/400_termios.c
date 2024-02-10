/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   400_termios.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 19:27:05 by antoda-s          #+#    #+#             */
/*   Updated: 2024/02/09 23:48:31 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief 				Gets the terminal settings
/// @param termios_p	Pointer to the termios settings structure
void	termios_getter(struct termios *termios_p)
{
	if (tcgetattr(STDIN_FILENO, termios_p) != 0)
		perror("tcgetattr() error");
}

/// @brief 				Sets the terminal settings from previous "getter"
/// @param termios_p	Pointer to the termios settings structure
void	termios_setter(struct termios *termios_p)
{
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, termios_p) != 0)
		perror("tcsetattr() error");
}

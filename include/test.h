/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 09:54:43 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/21 23:23:00 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../lib/libft/libft.h"
# include "error.h"

# ifndef MAXCOM
#  define MAXCOM 1000 // max number of letters to be supported
# endif
# ifndef MAXLIST
#  define MAXLIST 100 // max number of commands to be supported
# endif



// Clearing the shell using escape sequences


/* ************************************************************************** */
///	FUNCTIONS
/* ************************************************************************** */
void		ft_print(char *str);
char		*rl_gets(void *line_read);
void		init_history(HISTORY_STATE *state);
//HIST_ENTRY	*history_get_history_state(void);
void		printdirpath(void);
void		init_shell(void);

/* ************************************************************************** */
///	TEST3.C
/* ************************************************************************** */

/// @brief	Clears shell terminal using escape sequences
/// @param	None
void		clear(void);
/// @brief	Initializes shell
/// @param	None
void		init_shell(void);
/// @brief	Read a string, and add it to the history.
/// @param str	Pointer to the line to be read
/// @return		Pointer to the line read
int			get_input(char *str);
/// @brief	Print the current directory
void		print_dir_path(void);

/* ************************************************************************** */
///	TEST4.C
/* ************************************************************************** */

/// @brief 			Execute the command
/// @param parsed	Pointer to the command to be executed
void		exec_args(char **parsed);
/// @brief 				Execute 2 piped the command with pipe
/// @param parsed		Pointer to the first command to be executed
/// @param parsedpipe	Pointer to the second command to be executed
void		exec_args_piped(char **parsed, char **parsedpipe)


#endif

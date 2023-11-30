/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 19:28:06 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/30 18:11:12 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <signal.h>
# include <sys/stat.h>
# include <termios.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../lib/libft/libft.h"
# include "../include/error.h"
# include "../include/colors.h"
# include "../include/debug.h"

/* ************************************************************************** */
///	STRUCTS
/* ************************************************************************** */

int	g_exit_status;

/// @brief 				Enum to hold the token types
/// @param TOKEN_WS		Empty token
/// @param TOKEN_PIPE	Pipe token
/// @param TOKEN_R_IN	Redirection input token
/// @param TOKEN_R_OUT	Redirection output token
/// @param TOKEN_NAME	Name token
typedef enum e_token_type
{
	TOKEN_WS,
	TOKEN_PIPE,
	TOKEN_R_IN,
	TOKEN_R_OUT,
	TOKEN_NAME
}			t_token_type;

/// @brief 				Struct to hold the token variables (see t_token_type)
/// @param op			Token char set
/// @param size			Token char set length
/// @param type			Token type (as per enum t_token_type)
typedef struct s_operations
{
	const char		*op;
	int				size;
	t_token_type	type;
}				t_operations;

/// @brief 				Struct to hold the token variables
/// @param content		Token content
/// @param size			Token size
/// @param type			Token type
/// @param next			Next token
typedef struct s_token
{
	char			*content;
	int				size;
	t_token_type	type;
	struct s_token	*next;
}				t_token;

typedef struct s_redirection
{
	char	*name;
	int		flag;
	t_list	*heredoc;
}				t_redirection;

/// @brief 				Struct to hold the command variables
/// @param cmd			Command itself
/// @param argc			Number of arguments
/// @param argv			Arguments
/// @param out			Redirection output content
/// @param in			Redirection input content
typedef struct s_command
{
	char			*cmd;
	int				argc;
	char			**argv;
	t_redirection	out;
	t_redirection	in;
}				t_command;

/// @brief 				Struct to hold the minishell variables
/// @param commands		Commands to be executed
/// @param cmd_count	Number of commands
/// @param exit_status	Exit status
/// @param envp			Environment variables
/// @param termios_p	Terminal settings
typedef struct s_script
{
	t_command		*commands;
	int				cmd_count;
	int				exit_status;
	char			**envp;
	struct termios	termios_p;
}				t_script;

# ifndef CPIPE
#  define CPIPE 11
# endif
# ifndef INWORD
#  define INWORD 12
# endif

# ifndef OUTWORD
#  define OUTWORD 13
# endif

# ifndef INQUOTE
#  define INQUOTE 14
# endif

/* ************************************************************************** */
///	main.c
/* ************************************************************************** */



/* ************************************************************************** */
///	signal.c
/* ************************************************************************** */

/// @brief 		Signal processing functions setter
/// @param  	No parameter required
void	sig_setter(void);

/// @brief 			Handles signal SIGINT (Ctrl+C) and SIGQUIT (Ctrl+\)
///					Instead of exiting, the sig handler provides a new line
/// @param signum	The signal number
/// @return			void
void	sig_handler(int signum);

/// @brief 			Handles signal SIGINT (Ctrl+C) and SIGQUIT (Ctrl+\)
///					Instead of exiting, the sig handler provides a new line
/// @param signum	The signal number
/// @return			void
void	sig_handler_fork(int signum);

/// @brief 			Handles the signal SIGINT when in heredoc
///					Exits with status 130 Command terminated by user
/// @param signum	The signal number
/// @return			void
void	sig_handler_heredoc(int signum);

/* ************************************************************************** */
///	parser.c
/* ************************************************************************** */

/// @brief 			Checks if the number of arguments is valid
/// @param argc		Number of arguments
/// @return			SUCCESS if valid, ERROR if invalid
int		invalid_argc(int argc);

/// @brief 			Checks if str has paired quotes and double quotes
/// @param str		String to parse
/// @param c		Character to check
/// @return
int		invalid_pair(char *str, char *c);

/// @brief 				Checks if the quotes are valid
/// @param cmdline		Command line
/// @return				SUCCESS if valid, ERROR if invalid
int		invalid_quotes(char *line);

/// @brief 			Checks if the argument is valid
/// @param argv		Argument
/// @return			SUCCESS if valid, ERROR if invalid
int		invalid_line(char *line);



/* ************************************************************************** */
///	error.c
/* ************************************************************************** */

/// @brief 			Shows error and program sourcing it
/// @param msg		Message to show
/// @param system	Shows system error if true
/// @return			SUCCESS
int		return_error(const char *msg, int system);



/* ************************************************************************** */
///	debug.c
/* ************************************************************************** */

/// @brief 				Shows the function name and status
/// @param func_name	Name of the function
/// @param status		Status of the function
/// @return				Status of the function
int		show_func(const char *func_name, int status);

/* ************************************************************************** */
///	trimmer.c
/* ************************************************************************** */

/// @brief 				Trims the token command from whitespaces
/// @param token		Token to be trimmed
/// @param trimmer		Trimmer characters
char	*trimmer(char *line, const char *trimmer);

/* ************************************************************************** */
///	xxxxx.c
/* ************************************************************************** */


// ft_tokenize

//char *    ft_tokenize(char *input);
char	*ft_tokenize(const char *input, size_t *nbr_tokens);

// ft_strtok

char	*ft_strtok(char *src_str, char *delim);

//ft_execmd.c
void	ft_execmd(char **Token_list, int tokens_nbr);

//get_location.c

char	*get_location(char *command);

//ft_cd.c
int		cd_command(char **args);

#endif

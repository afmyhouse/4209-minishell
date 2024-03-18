/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 19:28:06 by antoda-s          #+#    #+#             */
/*   Updated: 2024/03/18 23:43:03 by antoda-s         ###   ########.fr       */
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
# include <sys/wait.h>
# include <sys/types.h>
# include <termios.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include "../include/error.h"
# include "../include/colors.h"
# include "../include/debug.h"
# include "../include/settings.h"

# define MAX_PATH_LEN 4096

extern int	g_exit_status;

/* ************************************************************************** */
///	STRUCTS
/* ************************************************************************** */

/// @brief 				Enum to hold the token types
/// @param TK_WS		Empty token
/// @param TK_PIPE	Pipe token
/// @param TK_I	Redirection input token
/// @param TK_O	Redirection output token
/// @param TK_NAME	Name token
typedef enum e_token_type
{
	TK_I,
	TK_O,
	TK_PIPE,
	TK_NAME,
	TK_EQUAL,
	TK_OR,
	TK_AND,
	TK_WS,
}			t_token_type;

typedef enum e_cmd_type
{
	CMD_EX,
	CMD_ECHO,
	CMD_CD,
	CMD_PWD,
	CMD_EXPORT,
	CMD_UNSET,
	CMD_ENV,
	CMD_EXIT,
	CMD_EQ
}			t_cmd_type;

/// @brief 				Struct to hold errors from execve
/// @param src_error	error from execve status
/// @param dest_error	error
typedef struct s_execve_error
{
	const int	src_error;
	const int	dest_error;
}				t_execve_error;

/// @brief 				Struct to hold the token variables (see t_token_type)
/// @param op			Token char set
/// @param size			Token char set length
/// @param type			Token type (as per enum t_token_type)
typedef struct s_operations
{
	const char		*op;
	int				size;
	t_token_type	type;
}				t_ops;

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

/// @brief 				Struct to hold the builtin command variables
/// @param bi_cmd		Builtin command
/// @param bi_func		Builtin function
/// @param va_args		Variable arguments
typedef struct s_bi_cmd
{
	const char		*bi_cmd;
	const void		*bi_func;
	void			*s;
	int				n;
}				t_bi_cmd;

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
/// @param cmds		Commands to be executed
/// @param cmd_count	Number of cmds
/// @param exit_status	Exit status
/// @param envp			Environment variables
/// @param termios_p	Terminal settings
typedef struct s_script
{
	t_command		*cmds;
	int				cmd_count;
	int				exit_status;
	char			**envp;
	char			**envt;
	char			**path;
	char			*home;
	struct termios	termios_p;
	int				mshlvl;
	int				fd[2];
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
//																			  */
//		     #    ####     ####												  */
//		     #   #    #   #    #											  */
//		     #   #    #   #    #											  */
//		     #   #    #   #    #											  */
//		     #   #    #   #    #											  */
//		     #   #    #   #    #											  */
//		     #    ####     ####												  */
//																			  */
/* ************************************************************************** */
/* ************************************************************************** */
///	100_main.c
/* ************************************************************************** */

/// @brief 		Creates array from system environment variables
/// @param envp system environment variables from main (... char **envp)
/// @return 	array copy of system environment variables
char	**envp_init(char **envp);

/// @brief 		Initialize basic int
/// @param s 	struct with pparams to initialize
void	struct_init(t_script *s);

/// @brief 				Initializes the shell and keeps looping until exit
/// @param script		Script structure (see minishell struct)
/// @return				void
int		ms_loop(t_script *script);

/// @brief 			Main function MINISHELL
/// @param argc		Number of arguments (NOT USED)
/// @param argv		Arguments (NOT USED)
/// @param envp		Environment variables
/// @return
int		main(int argc, char **argv, char **envp);

/* ************************************************************************** */
//																			  */
//		 ####     ####     ####												  */
//		     #   #    #   #    #											  */
//		     #   #    #   #    #											  */
//		 ####    #    #   #    #											  */
//		#        #    #   #    #											  */
//		#        #    #   #    #											  */
//		 ####     ####     ####												  */
//																			  */
/* ************************************************************************** */
/* ************************************************************************** */
///	200_signal.c
/* ************************************************************************** */
/// @brief 		Signal processing functions
/// @attention 	Error encountered while testing setter
/// @param		No parameter required
void	signal_setter(void);

void 	signal_selector(t_script *s);
void	sig_handler_parent(int signum);

/// @brief 		Signal processing functions
/// @attention 	Error encountered while testing setter
/// @param		No parameter required
void	signal_setter_parent(void);

/// @brief		Signal processing functions setter for loop
/// @param		No parameter required
void	signal_setter_fork(void);

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
//																			  */
//		 ####     ####     ####												  */
//		     #   #    #   #    #											  */
//		     #   #    #   #    #											  */
//		 ####    #    #   #    #											  */
//		     #   #    #   #    #											  */
//		     #   #    #   #    #											  */
//		 ####     ####     ####												  */
//																			  */
/* ************************************************************************** */
/* ************************************************************************** */
///	300_parser.c
/* ************************************************************************** */
/// @brief 				Builds an error message string to be displayed and
///						frees the tokens list, cmds list and returns 1.
/// @param cmds 		Commands list
/// @param cmd_count 	Number of commands
/// @param tk 			Head of the token list
/// @return 			1
int		back_to_loop(t_command *cmds, int cmd_count, t_token **tk);

/// @brief 		This function iterates through a linked list of tokens and
///				fills the command structure based on the type of token it
///				encounters.
/// @param head	Head of the token list
/// @param cmd	Command structure
/// @param i	Index
/// @param j	Index
/// @return		0 if success, 1 if failure
int		parse_commands(t_token *head, t_command *cmd, int i, int j);

/// @brief 				The script parser main function. All parsing starts here
/// @param script		The script pointer
/// @param line_buffer	The line buffer to parse
/// @return
int		parser(t_script *script, char **line_buffer);

/* ************************************************************************** */
///	301ms_syntax.c
/* ************************************************************************** */

/// @brief 				Builds an error message string to be displayed
///						when a syntax error is encountered.
/// @malloc				New strings
/// @free				New strings
/// @param tk_content	String argument to include in the error message
/// @return				Error message string
int		syntax_error_msg(char *tk_content, int errms, int errsys);

/// @brief		This function checks whether the given linked list, of tokens,
///				is a valid command syntaxically.
/// @param tk	Head of the token list
/// @return		0 if success, 1 if failure
int		syntax_checker(t_token *tk);

/* ************************************************************************** */
///	302ms_cmd.c
/* ************************************************************************** */
/// @brief			This function simply counts the number of pipes in our
///					linked list of tokens to determine the number of chained
///					cmds are in the line buffer.
/// @param head		Head of the token list
/// @return			Number of cmds
int		cmds_counter(t_token *head);

/* ************************************************************************** */
///	303ms_argc.c
/* ************************************************************************** */

/// @brief			Determines the amount of arguments each command
///					has so the argv can be malloced to the right size in the
///					following steps.
/// @param head		Head of the token list
/// @param script	Script pointer
/// @return			Trimmed content
void	args_counter(t_token *head, t_script *script);

/* ************************************************************************** */
///	304ms_redir.c
/* ************************************************************************** */

/// @brief 			Iniatilzes file names direction and remove quotes from names
/// @param cmds Struct witj info about files
/// @param max 		max number of files
/// @param head 	pointert o command struct hed
void	fnames_clear(t_command *cmds, int max, t_token *head);

/// @brief 			This function sets the open flags and opens the files
///					based on the type of redirection token it encounters
///					('<', '<<', '>', '>>').
/// @param head		Head of the token list
/// @param file		Redirection file structure
/// @return			0 if success, 1 if failure
int		redir(t_token *head, t_redirection *file);

/* ************************************************************************** */
///	305ms_heredoc.c
/* ************************************************************************** */

/// @brief 		Creates a node in the file linked list withe file name
///				and adds it to the back of list
/// @param file	Struct linked list node
void	fill_heredoc(t_redirection *file);

/* ************************************************************************** */
//																			  */
//		#    #    ####     ####												  */
//		#    #   #    #   #    #											  */
//		#    #   #    #   #    #											  */
//		 ####    #    #   #    #											  */
//		     #   #    #   #    #											  */
//		     #   #    #   #    #											  */
//		     #    ####     ####												  */
//																			  */
/* ************************************************************************** */
/* ************************************************************************** */
///	400ms_termios.c
/* ************************************************************************** */

/// @brief 				Gets the terminal settings
/// @param termios_p	Pointer to the termios settings structure
void	termios_getter(struct termios *termios_p);

/// @brief 				Sets the terminal settings. Main use is to FLUSH or
/// 					DRAIN any data remaining after missexecuting
/// @param termios_p	Pointer to the termios settings structure
void	termios_setter(struct termios *termios_p);

/* ************************************************************************** */
//																			  */
//		 ####     ####     ####												  */
//		#        #    #   #    #											  */
//		#        #    #   #    #											  */
//		 ####    #    #   #    #											  */
//		     #   #    #   #    #											  */
//		     #   #    #   #    #											  */
//		 ####     ####     ####												  */
//																			  */
/* ************************************************************************** */
/* ************************************************************************** */
///	501ms_tk_builder.c
/* ************************************************************************** */

/// @attention	>token builder< set of functions
/// @brief 		This function is here to treat off cases where a $ expansion
///				would lead to empty name tokens with the exception for an empty
///				token after a pipe.
/// @param head Head of the token list
/// @return		clean content
void	tk_rm_blank(t_token *head);

/// @attention	>token builder< set of functions
/// @brief 		Searches for a token type by token char set
/// @param s	String to be searched for token char set
/// @return		Struct with token type information: token char set, size
///				and token type
t_ops	tk_type_getter(const char *s);

/// @attention	>token builder< set of functions
/// @brief 		Initializes the tk_getter
/// @param str	String to be splitted in tokens
/// @param head	Head of the token list
/// @return		1 if success, 0 if error
int		tk_getter(char *str, t_token **tk_lst);

/// @attention	>token builder< set of functions
/// @brief 		Builds a list of tokens from string 'line'.
///				First it gets the proper token type and then expands the
///				the inset identifiers found, and also trims the tokens
///				extra whitespaces
/// @param line	string input with script
/// @param head	pointer to the head of the token list
/// @param s	script structure
/// @return		SUCCESS if valid, ERROR if invalid
int		tk_builder(char **line, t_token **tk, t_script *s);

/* ************************************************************************** */
///	502ms_tk_xpd.c
/* ************************************************************************** */

/// @attention	>token builder< set of functions
/// @brief 		it takes a char sequence and cpounts the number of splits needed
///				to build an array based of the splitter char '\"',  '\'',  '$'
/// @param otk 	char sequance to evaluate
/// @return		number of splits needed to properly create an array
int		tk_var_xpd_splits_count(char *otk);

/// @attention	>token builder< set of functions
/// @brief 		Initializes the array of expanded token
///				1st it fecths nmumber of splits
/// 			2nd mallocs necessary memory
/// @param otk 	char sequence to be splited -> copied into the new created array
/// @return		pointer to the newly created array
char	**tk_var_xpd_init(char *otk);

/// @attention	>token builder< set of functions
/// @brief 		for each token type NAME it creates an array wich is the split
///				at '\'', '\"' and '$'
/// @param otk 	original token
/// @return		the token's array with expanded args
char	**tk_var_xpd(char *otk);

/// @attention	>token builder< set of functions
/// @brief 				Replaces ARGS in a given string by the environment vars
///						by iterating through the string and replacing each
///						environment variable with its value.
/// @param otk		Token String to be parsed
/// @param envp			Environment variables
/// @param i			Index start
/// @param j			Index end
/// @return				String with ARGS replaced by envp vars
char	*tk_env_var_expander(char *otk, t_script *s);

/* ************************************************************************** */
///	503ms_tk_lst.c
/* ************************************************************************** */

/// @attention	>token builder< set of functions
/// @brief		checks if char is a valid identifier char ('_', alpha, digit)
/// @param c 	char to be checked
/// @return		SUCCESS or ERROR
int		var_name_checker(char c);

/// @attention	>token builder< set of functions
/// @brief		checks if char is a valid 1st identifier char ('_' or alpha)
/// @param c 	char to be checked
/// @return		SUCCESS or ERROR
int		var_firstchar(char c);

/// @attention	>token builder< set of functions
/// @brief 		Creates a new token node with {content, type, size, next}
/// @param str	String to be transformed into a toke
/// @param size	Token size
/// @param type	Token type (as per enum t_token_type see tk_type_getter
/// @return		pointer to the new added token
t_token	*tk_addnew(const char *str, int size, t_token_type type);

/// @attention	>token builder< set of functions
/// @brief 		Gets pointer to last node of token list
/// @param head	Pointer to token list
/// @return		last token list node
t_token	*tk_lst_last_getter(t_token *ltk);

/// @attention	>token builder< set of functions
/// @brief 					Adds a new token to the end of the token list
/// @param ltk	Pointer to token list
/// @param ntk	Pointer to new token
void	tk_lst_addback(t_token **ltk, t_token *ntk);

/* ************************************************************************** */
///	504ms_tk_xpd_count.c
/* ************************************************************************** */

/// @attention	>token builder< set of functions
/// @brief 		check is a '$' char is followed by valid valid identifier char
/// @param otk 	string sequence with a leading '$'
/// @param i 	index at '$' char
/// @return		addressed memory arg <i> is updated
void	tk_var_xpd_dolar_c(char *otk, int *i);

/// @attention	>token builder< set of functions
/// @brief 		looks for identifiers inside double quote string
///				if it find a '$' (var identifier init) it increments the
///				split index to point to next string sequence
/// @param otk	string sequence with a leading '\"'
/// @param spl 	split array indexer
/// @param i 	string sequence index
/// @return 	addressed memory <splits> and <i> updated
void	tk_var_xpd_dquote_c(char *otk, int *spl, int *i);

/// @attention	>token builder< set of functions
/// @brief		leading '\'' char sequences are ignored and treated as plain
///				literals, without any kind of replacement or substitution.
///				The only purpose is to update <i> index	to the position	of the
///				char after trailing '\''
/// @param otk 	'\'' leading sequence to browse till its trailing '\''
/// @param i 	string sequence index
/// @return		addressed memory arg <i> is updated
void	tk_var_xpd_squote_c(char *otk, int *i);

/// @attention	>token builder< set of functions
/// @brief 		any char sequence else (that is not leaded by a splitter char:
///				'\"',  '\'',  '$'
/// @param otk 	sequence to browse till a splitter char is found
/// @param i 	string sequence index
/// @return		addressed memory arg <i> is updated
void	tk_var_xpd_else_c(char *otk, int *i);

/* ************************************************************************** */
///	505ms_tk_xpd_filler.c
/* ************************************************************************** */

/// @attention	>token builder< set of functions
/// @brief
/// @param ntk
/// @param s
/// @return
char	*tk_xpd_var_filler(char *ntk, t_script *s);

/// @attention	>token builder< set of functions
/// @brief
/// @param ntk
/// @param s
/// @return
char	*tk_xpd_filler(char ***ntks, t_script *s);

/* ************************************************************************** */
///506ms_tk_split.c
/* ************************************************************************** */

/// @attention	>token builder< set of functions
/// @brief 		check is a '$' char is followed by valid valid identifier char
/// @param otk 	string sequence with a leading '$'
/// @param i 	index at '$' char
/// @return		addressed memory arg <i> is updated
///				alloced string with identifier name
char	*tk_var_xpd_dolar(char *otk, int *i);

/// @attention	>token builder< set of functions
/// @brief 		looks for identifiers inside double quote string
///				if it find a '$' (var identifier init) it increments the
///				split index to point to next string sequence
/// @param otk	string sequence with a leading '\"'
/// @param spl 	split array indexer
/// @param i 	string sequence index
/// @return 	addressed memory <splits> and <i> updated
///				alloced string with identifier name
void	tk_var_xpd_dquote(char *otk, char ***ntks, int *spl, int *i);

/// @attention	>token builder< set of functions
/// @brief		leading '\'' char sequences are ignored and treated as plain
///				literals, without any kind of replacement or substitution.
///				The only purpose is to update <i> index	to the position	of the
///				char after trailing '\''
/// @param otk 	'\'' leading sequence to browse till its trailing '\''
/// @param i 	string sequence index
/// @return		addressed memory arg <i> is updated
///				alloced string with identifier name
void	tk_var_xpd_squote(char *otk, char ***ntks, int *spl, int *i);

/// @attention	>token builder< set of functions
/// @brief 		any char sequence else (that is not leaded by a splitter char:
///				'\"',  '\'',  '$'
/// @param otk 	sequence to browse till a splitter char is found
/// @param i 	string sequence index
/// @return		addressed memory arg <i> is updated
///				alloced string with identifier name
void	tk_var_xpd_else(char *otk, char ***ntks, int *spl, int *i);

/* ************************************************************************** */
///507ms_tk_quotes.c
/* ************************************************************************** */

/// @brief 		fetchs for closed / unclosed quotes type " or '
///				the function must be called with the arg str (string)
///				starting with at a quotation mark.
///				The function seeks for the next occurrence of that quation mark
///				and sets str pointer to that next occurrence if found
///				or sets str pointer to the end {\0}
///				@malloc	: NOTHING
///				@free	: NOTHING
/// @param str	address of string, 1st char must be a quotation mark
/// @return		ERROR (unclosed), SUCCES (closed)
int		tk_quotes_checker(char **str);

/// @brief 		Unquotes a string. Special rules applies
///				- removes ' from limits = 'string'
///				- removes " from limts = "string", "string, string"
///				- (')  and (") are never inspected inside string
///				@malloc	: NOTHING
///				@free	: NOTHING
/// @param str	String to be unquoted
/// @return		A new unquoted string
char	*tk_xpd_unquote(char *str);

/// @brief			Replaces the token->content string with a new trimmed string
///					Trim removes leading and trailing white spaces
///	@malloc			TRIMMED string
///	@free			Pre TRIM string
/// @param tk	Head of the token list with token->content to be trimmed
/// @return			NOTHING
void	tk_trim_spaces(t_token *tk);

/* ************************************************************************** */
//																			  */
//		 ####     ####     ####												  */
//		#        #    #   #    #											  */
//		#        #    #   #    #											  */
//		 ####    #    #   #    #											  */
//		#    #   #    #   #    #											  */
//		#    #   #    #   #    #											  */
//		 ####     ####     ####												  */
//																			  */
/* ************************************************************************** */
/* ************************************************************************** */
///	600ms_env.c
/* ************************************************************************** */

char	**env_del_one(char *del, char **envx, int i);
// char	**env_del_one(char **envx, char *del);
char	**env_add_one(char **envx, char *add);


/// @brief 		This function gets the environment variable index
/// @param var 	variable to be found
/// @param envp Environment variables
/// @return		Index of the variable
int		env_var_index_getter(char *var, char **envx);

/// @brief 		This function sets the environment variable
/// @param val 	Value to be set
/// @param var 	Variable to be set
/// @param envp Environment variables
/// @return 	0 if success, -1 if error
int		env_var_setter(char *val, char *var, char ***envx);

/// @brief		This function iterates over the environment variables to
///				find whether or not the given variable (str) is defined and
///				returns the content or an empty freeable string.
/// @param var	Variable to be found
/// @param envp	Environment variables
/// @return		Content of the variable
char	*envx_var_getter(char *var, char **envx);

/// @brief		This function iterates over the environment variables to
///				find whether or not the given variable (str) is defined and
///				returns the content or an empty freeable string.
/// @param var	Variable to be found
/// @param envp	Environment variables
/// @return		Content of the variable
char	*env_var_getter(char *var, char **envp, char **envt);

/* ************************************************************************** */
//																			  */
//		 ####     ####     ####												  */
//		     #   #    #   #    #											  */
//		     #   #    #   #    #											  */
//		     #   #    #   #    #											  */
//		     #   #    #   #    #											  */
//		     #   #    #   #    #											  */
//		     #    ####     ####												  */
//																			  */
/* ************************************************************************** */
/* ************************************************************************** */
///	700exec_start.c
/* ************************************************************************** */

char	*add_forw_slash(char *str);
char	**path_fill(char **env, int p_line);
char	**split_paths(char **env);

/// @brief 			Executes the command
/// @param s 		Script contents and parameters including redirect info
/// @return 		SUCCESS or ERROR
int		execute(t_script *s);

/* ************************************************************************** */
///	705exec_type.c
/* ************************************************************************** */

int		bi_equal_check(t_script *s, int n, int i);


/// @brief 			Detects the type of commando to execute : a builtin and
/// 				what kind builtin or a system comand CMD_EX
/// @param cmd 		Command to execute
/// @return 		Command id
int		exec_type(char *cmd);

/* ************************************************************************** */
///	710exec_one.c
/* ************************************************************************** */
/// @brief 			Executes a builtin command according to its id
/// @param id 		Builtin command id
/// @param s 		Script contents and parameters including redirect info
/// @param i 		Index of the command to execute
/// @return 		SUCCESS or ERROR
int		exec_bi(int id, t_script *s, int i);

/// @brief 			Executes a command using the absolute path or the PATH
/// @param path 	Commands execution path
/// @param cmd 		Command to execute
/// @param env 		Environment variables
void	exec_ve(char **path, char **cmd, char **env);

/// @brief 			Executes a single command script in a fork
/// @param s 		Script contents and parameters including redirect info
/// @param path		Commands execution path
/// @return			SUCCESS or ERROR
int		exec_one_fork(t_script *s, char **path);

/// @brief 			Executes a single command script and checks if the command
///					is a builtin that doesnt need a fork (cd, unset, exit),
///					a builtin that requires a fork (echo, pwd, export, env)
///					or a system comamnd that requires a fork.
/// @param s 		Script contents and parameters including redirect info
/// @param path 	Commands execution path
/// @return 		SUCCESS or ERROR
int		exec_one(t_script *s, char **path);

int	exec_or(t_script *s, char **path);

int	exec_and(t_script *s, char **path);

/* ************************************************************************** */
///	720exec_many.c
/* ************************************************************************** */
/// @brief 			Executes the first command in a pipped script
/// @param s 		Script contents and parameters including redirect info
/// @param path 	Commands execution path
/// @param pipeout 	Pointer to the pipe to output result
/// @return 		SUCCESS or ERROR
int		exec_cmd_1(t_script *s, char **path, int *pipeout);

/// @brief 			Executes the command > 1 anmd < n in a pipped script
/// @param s 		Script contents and parameters including redirect info
/// @param path 	Commands execution path
/// @param pipes 	Pointer to the pipes array x 2 pipes
///					one pipe to read previous data, another to write results
/// @param pid 		NOTHING
int		exec_cmd_i(t_script *s, char **path, int **pipes, int i);

/// @brief 			Executes the last command in a pipped script
/// @param s 		Script contents and parameters including redirect info
/// @param path 	Commands execution path
/// @param pipein 	Pointer to the pipe with input data, resulted from previous
/// @param pid 		NOTHING
//void	exec_cmd_n(t_script *s, char **path, int *pipein, int pid)
int		exec_cmd_n(t_script *s, int *pipein);

/// @brief 			Selects the pipe for each inbetween command "i" and calls
/// 				the function to execute the command "i".
/// @param s 		Script contents and parameters including redirect info
/// @param path 	Commands execution path
/// @param pipe1 	Pointer to the first pipe
/// @param pipe2 	Pointer to the second pipe
/// @return 		SUCCESS or ERROR
int		exec_cmd_loop(t_script *s, char **path, int *pipe1, int *pipe2);

/// @brief 			Executes a script with multiple commands. The function will
/// 				fork to execute each command and will call the necessary
/// 				functions required too redirect pipes, files. The parent
/// 				waiting is performed here and will treat the exit status of
/// 				the child processes.
/// @param s 		Script contents and parameters including redirect info
/// @param path 	Commands execution path
/// @return 		SUCCESS or ERROR
int		exec_many(t_script *s, char **path);

/* ************************************************************************** */
///	730exec_childs.c
/* ************************************************************************** */
/// @brief 			Executes the first command in a pipe
/// @param s 		Script contents and parameters including redirect info
/// @param path 	Commands execution path
/// @param pipeout	Pointer to the pipe to output result
void	ex_child_1(t_script *s, int *pipeout);

/// @brief 			Executes the command in the middle of a pipe
/// @param s 		Script contents and parameters including redirect info
/// @param path 	Commands execution path
/// @param pipes 	Pointer to the pipes, IN and OUT
/// @param i 		Index of the command to execute
void	ex_child_i(t_script *s, int **pipes, int i);

/// @brief 			Executes the last command in a pipe
/// @param s 		Script contents and parameters including redirect info
/// @param path 	Commands execution path
/// @param pipein 	Pointer to the pipe
/// @param i
// void	ex_child_n(t_script *s, char **path, int *pipein, int i);
void	ex_child_n(t_script *s, int *pipein, int i);

/// @brief 			Executes the command (execeve or bi )
/// @param s 		Script contents and parameters including redirect info
/// @param path 	Commands execution path
/// @param id 		Command type
/// @param i 		Index of the command to execute
void	exec_go(t_script *s, char **path, int id, int i);

/* ************************************************************************** */
///	740exec_redirs.c
/* ************************************************************************** */
/// @brief 		After fork, child process calls this fucntion prepare redirect
///				from a file.
/// 			The input of next command will be a file isntead of a STDIN
/// 			If the  input is from a here doc instead, it will call
/// 			the heredoc function
/// @param s 	Script contents and parameters including redirect info
/// @param i 	Index of the command to be executed
/// @param path Commands execution path
void	in_redir(t_script *s, int i, char **path);

/// @brief 		After fork this fucntion is called to prepare redirect to a file
///				A previous output to STDOUT will be redirected to the file
/// @param s 	Script contents and parameters including redirect info
/// @param i 	Index of the command to be executed
/// @param path Commands execution path
void	out_redir(t_script *s, int i, char **path);


/* ************************************************************************** */
///	750exec_heredoc.c
/* ************************************************************************** */
/// @brief 			This function notifies heredoc error message
/// @param msg 		Content to be printed
void	error_message_heredoc(char *msg);

/// @brief		This function reads the user's input until it finds the
/// 			delimiters set in heredoc linked list. It stores the input only
/// 			for the last delimiter and places it in the pipe for later use
/// 			as the input redirection.
/// @param h 	Pointer to the heredoc linked list
/// @param pipe Pointer to the pipe to output result;

/// @brief		This function first initializes a pipe in which we can write
/// 			the content that we'll read from the user.
/// @param s 	Script contents and parameters including redirect info
/// @param i 	Index of the command to be executed
/// @param path Commands execution path
void	heredoc(t_script *s, int i, char **path);


/* ************************************************************************** */
///	760exec_pipes.c
/* ************************************************************************** */
//// @brief 		This function initializes pipes needed to redirect the
///					output of the previous cmd into the next one.
/// 				It initializes a pipe for the next result of a command and
/// @param path 	Commands execution path
/// @param pipe1 	Pointer to the pipe to read previous data
/// @param pipe2 	Pointer to the pipe to write results
/// @return 		Pointer to the pipes array x 2 pipes
int		**pipe_init(char **path, int *pipe1, int *pipe2);

/// @brief 		This fucntion is usefull to manage the closing of pipes as long
/// 			they are not nedeed. It called when a child process is done with
/// 			its pipe (previous) or whenever there are errors creating
///				or the dup2 of fd fails.
/// @param pa 	pipa a, initial pipe of an odd cmd i (in a list from 1 to n-1)
/// @param pb 	pipe b, initial pipe of an even cmd i (in a list from 1 to n-1)
void	pipe_closer(int *pa, int *pb);

/// @brief 			This function is called every time we have to dup2 a pipe.
/// 				It takes the pipe, and the extremity we have to dup and
///					replace it with the corresponding STDIN/STDOUT.
/// @param pipe 	The pipe to dup.
/// @param end 		The extremity we have to dup.
/// @return
int		pipe_std_setter(int *pipe, int end);


/* ************************************************************************** */
///	799exec_errors.c
/* ************************************************************************** */
int		fork_error(char **path_env);
int		pipe_error(char **path_env);


/* ************************************************************************** */
//																			  */
//		 ####     ####     ####												  */
//		#    #   #    #   #    #											  */
//		#    #   #    #   #    #											  */
//		 ####    #    #   #    #											  */
//		#    #   #    #   #    #											  */
//		#    #   #    #   #    #											  */
//		 ####     ####     ####												  */
//																			  */
/* ************************************************************************** */

/* ************************************************************************** */
///	810_bi_echo.c
/* ************************************************************************** */
/// @brief  		Checks if the echo command has the flag '-n'
/// @param str 		Argument string
/// @return 		1 if true, 0 if false
int		bi_echo_flag(char *str);

/// @brief 			Builtin echo command
/// @param command	Builtin command arguments
/// @return			SUCCESS if success, ERROR if error
//int	bi_echo(t_command cmds)
int		bi_echo(t_script *s, int n);

/// @brief 			Builtin echo command env var '_' update (last cmd)
/// @param s		Parsed script with command(s) to execute
/// @param n		Index of cmd to executes
/// @return			SUCCESS if success, ERROR if error
int		bi_env_upd(t_script *s, int n);


/* ************************************************************************** */
///	820_bi_cd.c
/* ************************************************************************** */
// @brief 			Changes the current directory and updates env var PWD OLDPWD
/// @param path 	New directory path
/// @param envp 	Environment variables
/// @return 		SUCCESS or ERROR
int		change_dir(char *path, char ***envp);

/// @brief 			Builtin cd command
/// @param args		Builtin command arguments
/// @return			SUCCESS or ERROR
int		bi_cd(t_script *s, int n);

/* ************************************************************************** */
///	830_bi_pwd.c
/* ************************************************************************** */
/// @brief 			Builtin pwd command
/// @param void		Builtin command arguments not required
/// @return			SUCCESS or ERROR
int		bi_pwd(t_script *s, int n);


/* ************************************************************************** */
///	840_bi_export.c
/* ************************************************************************** */
/// @brief		Test validity of shell variables name
/// @param var	Variable name to be tested
/// @return		SUCCESS or ERROR
int		var_name_check(char *var);

/// @brief  	Update the value of an existing variable either at envt or envp
/// @param s 	Script structure with commans and args
/// @param n 	Index of command to be executed
/// @param i 	Index of argument to be checked
void	bi_export_upd_var(t_script *s, int n, int i);

/// @brief  	Checks if export NEW environment variables or update existing
/// 			variables and also if the variables exist already in environment
/// 			temporary array
/// @param s 	Script structure with commans and args
/// @param n 	Index of command to be executed
/// @param i 	Index of argument to be checked

void	bi_export_new_var(t_script *s, int n, int i);
/// @brief 			Export PERMANENT environment variables
/// @param s 		Script structure with commans and args
/// @param n 		Index of command to be executed
/// @return 		SUCCESS or ERROR
int		bi_export(t_script *s, int n);

/* ************************************************************************** */
///	845_bi_export_status.c
/* ************************************************************************** */


/// @brief 		Export array method : ordered and declare statement
/// @param str 	Variable to be printed
void	export_print(char *str);

/// @brief 		Alphatecially ordered array
/// @param src 	Array to order
/// @return 	Ordered array
char	**ordered_array(char **d, char t, int n, int j);

/// @brief 		Export the environment variables
/// @param s 	Script structure with commans and args
/// @param n 	Index of command to be executed
/// @return 	SUCCESS or ERROR
int		export_status(t_script *s, int n);

/* ************************************************************************** */
///	850_bi_unset.c
/* ************************************************************************** */
/// @brief 			Remove a variable from the PERMANENT environment
/// @param s 		Arguments passed to unset command
/// @param n 		Current argument (variable)
/// @return			Updated environment variables
int		bi_unset(t_script *s, int n);

/// @brief 			Remove a variable from the TEMPORARY environment
/// @param s 		Arguments passed to unset command
/// @param n 		Current argument (variable)
/// @return			Updated environment variables
int		bi_unset_envt(t_script *s, int n);


/* ************************************************************************** */
///	860_bi_env.c
/* ************************************************************************** */
/// @brief 			Builtin env command
/// @param args		Builtin command arguments
/// @param envp		Environment variables
/// @return			SUCCESS or ERROR
int		bi_env(t_script *s, int n);


/* ************************************************************************** */
///	870_bi_exit.c
/* ************************************************************************** */
/// @brief 			Builtin 'exit' command argument checker
/// @param str		Builtin 'exit' argument string
/// @return			SUCSESS or ERROR
int		ft_is_str_digit(char *str);

/// @brief 			Shows error and program sourcing it
/// @param msg		Message to show
/// @param system	Shows system error if true
/// @return			SUCCESS
int		exit_error_args(const char *msg, int system);

/// @brief 			Shows exit() NOT numeric arg error
/// @param msg 		Message to show
/// @param system 	Shows system error if true
/// @return 		system errno
//int		exit_error_notnum(const char *msg, int system);

/// @brief 		Exit function with error message
/// @param s 	Script structure with commans and args
/// @param arg 	Argument to be checked
/// @param msg 	Message to be shown
/// @param sys 	System error
void	exit_go(t_script *s, char *arg, char *msg, int sys);

/// @brief 			Builtin exit command
/// @param args		Builtin command arguments
/// @return			exit status or ERROR
int		bi_exit(t_script *s, int n);


/* ************************************************************************** */
///	880_bi_equal.c
/* ************************************************************************** */
/// @brief 			Update EXISTING TEMPORARY environment variables
/// @param s 		Script structure with commans and args
/// @param n 		Index of command to be executed
/// @param i 		Index of argument to be checked
void	bi_equal_upd(t_script *s, int n, int i);

/// @brief 			Creates NEW TEMPORARY environment variables
/// @param s 		Script structure with commans and args
/// @param n 		Index of command to be executed
/// @param i 		Index of argument to be checked
void	bi_equal_new(t_script *s, int n, int i);

/// @brief 			Export TEMPORARY environment variables
/// @param s 		Script structure with commans and args
/// @param n 		Index of command to be executed
/// @return 		SUCCESS or ERROR
int		bi_equal(t_script *s, int n);

/* ************************************************************************** */
///	890_bi_append.c
/* ************************************************************************** */
/// @brief 			Looks for += embedded signs and call bi_append_new
/// @param s 		Script structure with commans and args
/// @param n 		Index of command to be executed
/// @return 		SUCCESS or ERROR
int		bi_append(t_script *s, int n, int i);

/* ************************************************************************** */
//																			  */
//		 ####     ####     ####												  */
//		#    #   #    #   #    #											  */
//		#    #   #    #   #    #											  */
//		 ####    #    #   #    #											  */
//		     #   #    #   #    #											  */
//		     #   #    #   #    #											  */
//		 ####     ####     ####												  */
//																			  */
/* ************************************************************************** */

/* ************************************************************************** */
///	900free.c
/* ************************************************************************** */
/// @brief 			Frees the environment variables
/// @param my_envp	Environment variables
int		free_array(char **array, int err);

/// @brief 		Frees the token list
/// @param head	Head of the token list
/// @return		1 if success, 0 if failure
int		free_tokens(t_token **head);

/// @brief 			Clears args on cmds struct list and frees nodes
/// @param cmd 		list pointer
/// @param cmd_idx 	quantity of nodes to clear and free
/// @return 		SUCCESS or ERROR ?? needs coherence check
int		free_commands(t_command *cmd, int cmd_idx);

/// @brief 		Frees the path, envt, envp and the commands
/// @param s 	Struct with pointer to be freed
int		free_exit(t_script *s, int errms);

/// @brief 			Frees the path and the commands
/// @param script 	Script to be freed
/// @param path 	Path to be freed
void	free_cmds_path(t_script *script, char **path);

/// @brief 			Shows error and program sourcing it and exit(1) freeing
/// 				allocated vars
/// @param msg 		Message to show
/// @param errms 	Error message
/// @param s 		Script to be freed
/// @param path 	Path to be freed
void	exit_forks(char *msg, int errms, t_script *s, char **path);

/* ************************************************************************** */
///	910errors.c
/* ************************************************************************** */
/// @brief 			Shows error and program sourcing it
/// @param msg		Message to show
/// @param system	Shows system error if true
/// @return			SUCCESS
int		export_error(const char *msg, int system);

/// @brief 			Shows error and program sourcing it
/// @param msg		Message to show
/// @param system	Shows system error if true
/// @return			SUCCESS
int	flags_error(const char *msg, char *flags, int errms);

/// @brief 			Shows error and program sourcing it
/// @param msg		Message to show
/// @param system	Shows system error if true
/// @return			SUCCESS
int		return_error(const char *msg, int errms, int errbash);


/* ************************************************************************** */
///	999_debug.c
/* ************************************************************************** */
void	execute_show(t_script *s);
void	show_func_msg(const char *msg);
/// @brief 				Shows the function name and status
/// @param func_name	Name of the function
/// @param status		Status of the function
/// @return				Status of the function
int		show_func(const char *func_name, int status, char *msg);
/// @brief 				This function prints the environment variables
/// @param envp			Environment variables
/// @return				void
void	show_array(char **array, const char *name);
void	show_token_list(t_token *token);
char	*ft_var_address(const char *varname, void *var);
void	show_pointer(const char *func, int status, const char *msg, void *ptr);

#endif

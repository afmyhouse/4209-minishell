/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoffaux <sgoffaux@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 11:04:53 by sgoffaux          #+#    #+#             */
/*   Updated: 2021/10/08 14:36:38 by sgoffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/stat.h>
# include <termios.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

# define MAX_PATH_LEN 4096

int	g_exit_status;

typedef enum e_token_type
{
	TOKEN_EAT,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_NAME
}			t_token_type;

typedef struct s_operations
{
	const char		*op;
	int				size;
	t_token_type	type;
}				t_operations;

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

typedef struct s_command
{
	char			*cmd;
	int				argc;
	char			**argv;
	t_redirection	out;
	t_redirection	in;
}				t_command;

typedef struct s_script
{
	t_command		*commands;
	int				cmd_count;
	int				exit_status;
	char			**envp;
	struct termios	termios_p;
}				t_script;

// builtin
int				builtin_cd(t_command command, char **envp);
int				builtin_echo(t_command command);
int				builtin_env(char **envp, t_command command);
int				builtin_exit(t_command command, int cmd_count, char *str);
int				builtin_export(t_script *script, t_command command);
int				builtin_pwd(char **envp);
int				builtin_unset(t_script *script, t_command command);
void			error_message_export(char *message);
int				copy_env(char **array1, char **array2);
int				env_len(char **array);
char			*copy_no_plus(char *argvar);
int				checkvalid(char *str);
int				export_check(char **str, t_command cmd);
int				check_space_export(char *str);

// execution
int				fork_error(char **path_env);
int				pipe_error(char **path_env);
int				one_cmd(t_script *script, char **path_env);
int				pipex(t_script *script, char **path_env);
void			first_child(t_script *script, char **path_env, int *pipe1);
void			middle_child(t_script *s, char **path_env, int **pipes, int i);
void			last_child(t_script *s, char **path_env, int *pipein, int i);
void			in_redir(t_script *script, int i, char **path_env);
void			out_redir(t_script *script, int i, char **path_env);
void			close_pipes(int *pipe1, int *pipe2);
int				pipe_dup(int *pipe, int mod, int std);
void			cmd_builtin(t_script *script, char **path_env, int ret, int i);
int				first_cmd(t_script *script, char **path_env, int *pipe1);
int				mid_loop(t_script *s, char **path_env, int *pipe1, int *pipe2);
void			last_cmd(t_script *s, char **path_env, int *pipein, int pid);
int				handle_cmd(t_script *script);
int				check_builtin(char *cmd);
int				handle_builtin(int ret, t_script *script, int i);
void			heredoc(t_script *script, int i, char **path_env);
char			**split_paths(char **env);
int				check_syntax(t_token *head);

// parsing
int				get_cmd_count(t_token *head);
int				return_error(const char *msg, int system);
void			get_num_args(t_token *head, t_script *script);
void			set_filenames_null(t_command *commands, int max, t_token *head);
int				parse(t_script *script, char **line_buf);
int				odd_before(char **str, int i, char c);
int				odd_after(char **str, int i, char c);
void			free_split(char **split);
char			*replace_env_var(char *line_buf, char **envp, int i, int j);
char			*get_env_content(char *str, char **envp);
t_token			*create_token(const char *string, int size, t_token_type type);
void			add_token(t_token **head, t_token *new_token);
t_operations	search_token_type(const char *s);
char			*remove_quotes(char *str);
int				tokenizer(char *str, t_token **head);
void			remove_blank_tokens(t_token *head);
void			fill_heredoc(t_redirection *file);

// srcs
int				free_commands(t_command *cmd, int cmd_idx);
int				free_tokens(t_token **head);
void			free_path_env(char **path_env);
void			free_cmds_path(t_script *script, char **path_env);
void			close_free_exit(t_script *s, char **path_env, int *p1, int *p2);
void			sig_handler(int signum);
void			sig_handler_fork(int signum);
void			sig_handler_heredoc(int signum);

#endif

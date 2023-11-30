/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3ms_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 23:28:14 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/30 22:52:52 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/// @brief 		This function is here to treat off cases where a $ expansion
///				would lead to empty name tokens with the exception for an empty
///				token after a pipe.
/// @param head Head of the token list
/// @return		clean content
void	remove_blank_tokens(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		if (head->type != TOKEN_PIPE && head->next && !head->next->content[0])
		{
			tmp = head->next->next;
			free(head->next->content);
			free(head->next);
			head->next = tmp;
		}
		else
			head = head->next;
	}
}

/// @brief		This function checks whether the given linked list, of tokens,
///				is a valid command syntaxically.
/// @param head	Head of the token list
/// @return		0 if success, 1 if failure
int	check_syntax(t_token *head)
{
	t_token	*tmp;

	tmp = head;
	if (head && head->type == TOKEN_PIPE)
		return (return_error("Syntax error", 0));
	while (head)
	{
		if (!head->next && (head->type == TOKEN_PIPE
				|| head->type == TOKEN_R_IN
				|| head->type == TOKEN_R_OUT))
			return (return_error("Syntax error", 0));
		if (head->type == TOKEN_PIPE && head->next
			&& head->next->type == TOKEN_PIPE)
			return (return_error("Syntax error", 0));
		if ((head->type == TOKEN_R_OUT || head->type == TOKEN_R_IN)
			&& (head->next && head->next->type != TOKEN_NAME))
			return (return_error("Syntax error", 0));
		head = head->next;
	}
	return (0);
}

/// @brief			This function simply counts the number of pipes in our
///					linked list of tokens to determine the number of chained
///					commands are in the line buffer.
/// @param head		Head of the token list
/// @return			Number of commands
int	get_cmd_count(t_token *head)
{
	int	count;

	count = 0;
	while (head)
	{
		if (!count)
			count = 1;
		if (head->type == TOKEN_PIPE)
			count ++;
		head = head->next;
	}
	return (count);
}

/// @brief		This function simply trims the leading and trailing whitespace
///				that can be found when replacing an environment variable.
/// @param head	Head of the token list
/// @return		Trimmed content
static void	trim_spaces(t_token *head)
{
	char	*tmp;

	while (head)
	{
		tmp = head->content;
		head->content = ft_strtrim(tmp, " \t\v\r\n\f");
		free(tmp);
		head = head->next;
	}
}

/// @brief		This function determines the amount of arguments each command
///				has so the argv can be malloced to the right size in the
///				following steps.
/// @param head	Head of the token list
/// @param script	Script pointer
/// @return		Trimmed content
void	get_num_args(t_token *head, t_script *script)
{
	t_token	*tmp;
	int		i;

	i = 0;
	while (i < script->cmd_count)
	{
		script->commands[i].argc = 0;
		tmp = head;
		while (head && head->type != TOKEN_PIPE)
		{
			if (head->type == TOKEN_NAME && (tmp->type != TOKEN_R_IN
					&& tmp->type != TOKEN_R_OUT))
				script->commands[i].argc++;
			tmp = head;
			head = head->next;
		}
		if (head)
			head = head->next;
		i++;
	}
}
/*
set_filenames_null(t_command *commands, int max, t_token *head):
	This function does two things:
	1. Sets the redirection file names to null so that we can differentiate
		between them being set or not.
	2. Iterates over our linked list of tokens and removes the outer
		quotation marks.
*/
void	set_filenames_null(t_command *commands, int max, t_token *head)
{
	int	i;

	i = -1;
	while (++i < max)
	{
		commands[i].in.name = NULL;
		commands[i].out.name = NULL;
		commands[i].in.heredoc = NULL;
	}
	while (head)
	{
		head->content = remove_quotes(head->content);
		head = head->next;
	}
}

/// @brief 		This function iterates through a linked list of tokens and
///				fills the command structure based on the type of token it
///				encounters.
/// @param head	Head of the token list
/// @param cmd	Command structure
/// @param i	Index
/// @param j	Index
/// @return		0 if success, 1 if failure
static int	parse_commands(t_token *head, t_command *cmd, int i, int j)
{
	while (head)
	{
		cmd[i].argv = malloc(sizeof(char *) * (cmd[i].argc + 1));
		if (!cmd[i].argv)
			return (1);
		j = 0;
		while (head && head->type != TOKEN_PIPE)
		{
			if (head->type == TOKEN_NAME)
				cmd[i].argv[j++] = ft_strdup(head->content);
			else if (head->type == TOKEN_R_IN && redir(head, &cmd[i].in))
				return (free_commands(cmd, i + 1));
			else if (head->type == TOKEN_R_OUT && redir(head, &cmd[i].out))
				return (free_commands(cmd, i + 1));
			if (head->type == TOKEN_R_IN || head->type == TOKEN_R_OUT)
				head = head->next;
			if (head)
				head = head->next;
		}
		if (head)
			head = head->next;
		cmd[i].argv[j] = NULL;
		i++;
	}
	return (0);
}

/*
redir:
	This function sets the open flags and opens the files based on the type of
	redirection token it encounters ('<', '<<', '>', '>>').
*/

/// @brief 			This function sets the open flags and opens the files
///					based on the type of redirection token it encounters
///					('<', '<<', '>', '>>').
/// @param head		Head of the token list
/// @param file		Redirection file structure
/// @return			0 if success, 1 if failure
static int	redir(t_token *head, t_redirection *file)
{
	int		ret;

	if (file->name)
		free(file->name);
	if (!head->next || head->next->type != TOKEN_NAME)
		return (0);
	file->name = ft_strdup(head->next->content);
	if (!ft_strncmp(head->content, ">>", 2))
		file->flag = (O_CREAT | O_APPEND | O_RDWR);
	else if (!ft_strncmp(head->content, "<<", 2))
		fill_heredoc(file);
	else if (!ft_strncmp(head->content, ">", 1))
		file->flag = (O_CREAT | O_TRUNC | O_RDWR);
	else if (!ft_strncmp(head->content, "<", 1))
		file->flag = O_RDONLY;
	if (file->flag == -1)
		return (0);
	ret = open(file->name, file->flag, 0644);
	if (ret == -1)
		return (return_error(file->name, 1));
	close(ret);
	return (0);
}


/// @brief 				The script parser main function. All parsing starts here
/// @param script		The script pointer
/// @param line_buffer	The line buffer to parse
/// @return
int	parser(t_script *script, char **line_buffer)
{
	t_token	*head;

	head = NULL;
	*line_buffer = readline("\001\033[1;36m\002Minishell ᐅ \001\033[0m\002");
	if (!*line_buffer)
		return (show_func(__func__, MALLOC_ERROR));
	add_history(*line_buffer);
	if (tokenize(line_buffer, &head, script))
		return (free_tokens(&head));
	remove_blanks_tokens(head);
	if (check_syntax(head))
		return (free_tokens(&head));
	script->cmd_count = get_cmd_count(head);
	script->commands = malloc(sizeof(t_command) * script->cmd_count);
	if (!script->commands || script->cmd_count <= 0)
		return (free_tokens(&head));
	trim_spaces(head);
	get_num_args(head, script);
	set_filenames_null(script->commands, script->cmd_count, head);
	if (parse_commands(head, script->commands, 0, 0))
		return (free_tokens(&head));
	free_tokens(&head);
	return (0);
}

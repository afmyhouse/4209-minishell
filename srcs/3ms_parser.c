/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3ms_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 23:28:14 by antoda-s          #+#    #+#             */
/*   Updated: 2023/12/04 23:57:54 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/// @brief		This function checks whether the given linked list, of tokens,
///				is a valid command syntaxically.
/// @param head	Head of the token list
/// @return		0 if success, 1 if failure
int	check_syntax(t_token *head)
{
	// t_token	*tmp;

	// tmp = head;
	show_func(__func__, MY_START);
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
	show_func(__func__, SUCCESS);
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

	show_func(__func__, MY_START);
	count = 0;
	while (head)
	{
		if (!count)
			count = 1;
		if (head->type == TOKEN_PIPE)
			count ++;
		head = head->next;
	}
	show_func(__func__, SUCCESS);
	return (count);
}

/// @brief		This function simply trims the leading and trailing whitespace
///				that can be found when replacing an environment variable.
/// @param head	Head of the token list
/// @return		Trimmed content
void	trim_spaces(t_token *head)
{
	char	*tmp;

	show_func(__func__, MY_START);
	while (head)
	{
		tmp = head->content;
		head->content = ft_strtrim(tmp, " \t\v\r\n\f");
		free(tmp);
		head = head->next;
	}
	show_func(__func__, SUCCESS);
	return ;
}

/// @brief			This function determines the amount of arguments each command
///					has so the argv can be malloced to the right size in the
///					following steps.
/// @param head		Head of the token list
/// @param script	Script pointer
/// @return			Trimmed content
void	get_num_args(t_token *head, t_script *script)
{
	t_token	*tmp;
	int		i;

	show_func(__func__, MY_START);
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
	show_func(__func__, SUCCESS);
	return ;
}

/// @brief 			Iniatilzes file names direction and remove quotes from names
/// @param commands Struct witj info about files
/// @param max 		max number of files
/// @param head 	pointert o command struct hed
void	set_filenames_null(t_command *commands, int max, t_token *head)
{
	int	i;

	show_func(__func__, MY_START);
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
	show_func(__func__, SUCCESS);
	return ;
}

/// @brief 		This function iterates through a linked list of tokens and
///				fills the command structure based on the type of token it
///				encounters.
/// @param head	Head of the token list
/// @param cmd	Command structure
/// @param i	Index
/// @param j	Index
/// @return		0 if success, 1 if failure
int	parse_commands(t_token *head, t_command *cmd, int i, int j)
{
	show_func(__func__, MY_START);
	while (head)
	{
		cmd[i].argv = malloc(sizeof(char *) * (cmd[i].argc + 1));
		if (!cmd[i].argv)
		{
			show_func(__func__, ERROR);
			return (1);
		}
		j = 0;
		while (head && head->type != TOKEN_PIPE)
		{
			if (head->type == TOKEN_NAME)
				cmd[i].argv[j++] = ft_strdup(head->content);
			else if (head->type == TOKEN_R_IN && redir(head, &cmd[i].in))
			{
				printf("%s : exit 01\n", __func__);
				show_func(__func__, SUCCESS);
				return (free_commands(cmd, i + 1));
			}
			else if (head->type == TOKEN_R_OUT && redir(head, &cmd[i].out))
			{
				printf("%s : exit 02\n", __func__);
				show_func(__func__, SUCCESS);
				return (free_commands(cmd, i + 1));
			}
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
	printf("%s : exit 03\n", __func__);
	show_func(__func__, SUCCESS);
	return (0);
}

/// @brief 			This function sets the open flags and opens the files
///					based on the type of redirection token it encounters
///					('<', '<<', '>', '>>').
/// @param head		Head of the token list
/// @param file		Redirection file structure
/// @return			0 if success, 1 if failure
int	redir(t_token *head, t_redirection *file)
{
	int		ret;

	show_func(__func__, MY_START);
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
	show_func(__func__, SUCCESS);
	return (0);
}

/// @brief 		Creates a node in the file linked list withe file name
///				and adds it to the back of list
/// @param file	Struct linked list node
void	fill_heredoc(t_redirection *file)
{
	t_list	*tmp;

	show_func(__func__, MY_START);
	tmp = ft_lstnew(ft_strdup(file->name));
	if (file->heredoc == NULL)
		file->heredoc = tmp;
	else
		ft_lstadd_back(&file->heredoc, tmp);
	file->flag = -1;
	show_func(__func__, SUCCESS);
}

/// @brief 				The script parser main function. All parsing starts here
/// @param script		The script pointer
/// @param line_buffer	The line buffer to parse
/// @return
int	parser(t_script *script, char **line_buffer)
{
	t_token	*head;

	show_func(__func__, MY_START);
	head = NULL;
	*line_buffer = readline("\001\033[1;36m\002Minishell ᐅ \001\033[0m\002");
	if (!*line_buffer)
		return (show_func(__func__, MALLOC_ERROR));
	add_history(*line_buffer);
	if (tokenize(line_buffer, &head, script))
		return (free_tokens(&head));
	remove_blank_tokens(head);
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
	{
		show_func(__func__, SUCCESS);
		return (free_tokens(&head));
	}
	show_func(__func__, SUCCESS);
	//free_tokens(&head);
	return (0);
}

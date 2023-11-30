/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 14:38:46 by sgoffaux          #+#    #+#             */
/*   Updated: 2023/11/30 22:22:05 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
redir:
	This function sets the open flags and opens the files based on the type of
	redirection token it encounters ('<', '<<', '>', '>>').
*/
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

/*
parse_commands:
	This function iterates through a linked list of tokens and fills the command
	structure based on the type of token it encounters.
*/
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
			else if (head->type == TOKEN_REDIR_IN && redir(head, &cmd[i].in))
				return (free_commands(cmd, i + 1));
			else if (head->type == TOKEN_REDIR_OUT && redir(head, &cmd[i].out))
				return (free_commands(cmd, i + 1));
			if (head->type == TOKEN_REDIR_IN || head->type == TOKEN_REDIR_OUT)
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
tokenize:
	This function splits the readline buffer into tokens (eg. pipes, command names,
	flags, etc.) then goes through each token and replaces any environment
	variables that need to be replaced.
*/
static int	tokenize(char **line, t_token **head, t_script *s)
{
	t_token	*tmp;
	char	*bis;

	if (!tokenizer(*line, head))
		return (return_error("Syntax Error", 0));
	tmp = *head;
	while (tmp)
	{
		bis = tmp->content;
		tmp->content = replace_env_var(bis, s->envp, 0, 0);
		free(bis);
		tmp = tmp->next;
	}
	return (0);
}

/*
trim_spaces:
	This function simply trims the leading and trailing whitespace that can be
	found when replacing an environment variable.
*/
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

/*
parse:
	This function calls readline to wait for an input from the user, adds the
	command to the history, then goes on to parse the string.
	The parsing is done in multiple steps, starting with a lexer (tokenizer)
	that will split the string into workable tokens that can be parsed into
	our command structure.
*/
int	parse(t_script *script, char **line_buf)
{
	t_token	*head;

	head = NULL;
	*line_buf = readline("\001\033[1;36m\002Minishell ᐅ \001\033[0m\002");
	if (!*line_buf)
		return (2);
	add_history(*line_buf);
	if (tokenize(line_buf, &head, script))
		return (free_tokens(&head));
	remove_blank_tokens(head);
	if (check_syntax(head))
		return (free_tokens(&head));
/* ************************************************************************** */
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoffaux <sgoffaux@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 14:54:29 by sgoffaux          #+#    #+#             */
/*   Updated: 2021/10/07 16:39:33 by sgoffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
remove_blank_tokens(t_token *head):
	This function is here to treat off cases where a $ expansion would lead to 
	empty name tokens with the exception for an empty token after a pipe.
*/
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

/*
get_cmd_count(t_token *head):
	This function simply counts the number of pipes in our linked list of 
	tokens to determine the number of chained commands are in the line buffer.
*/
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

/*
get_num_args(t_token *head, t_script *script):
	This function determines the amount of arguments each command has so the 
	argv can be malloced to the right size in the following steps.
*/
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
			if (head->type == TOKEN_NAME && (tmp->type != TOKEN_REDIR_IN
					&& tmp->type != TOKEN_REDIR_OUT))
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
check_syntax(t_token *head):
	This function checks whether the given linked list of tokens is a valid 
	command syntaxically.
*/
int	check_syntax(t_token *head)
{
	t_token	*tmp;

	tmp = head;
	if (head && head->type == TOKEN_PIPE)
		return (return_error("Syntax error", 0));
	while (head)
	{
		if (!head->next && (head->type == TOKEN_PIPE
				|| head->type == TOKEN_REDIR_IN
				|| head->type == TOKEN_REDIR_OUT))
			return (return_error("Syntax error", 0));
		if (head->type == TOKEN_PIPE && head->next
			&& head->next->type == TOKEN_PIPE)
			return (return_error("Syntax error", 0));
		if ((head->type == TOKEN_REDIR_OUT || head->type == TOKEN_REDIR_IN)
			&& (head->next && head->next->type != TOKEN_NAME))
			return (return_error("Syntax error", 0));
		head = head->next;
	}
	return (0);
}

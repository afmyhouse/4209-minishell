/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   300_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 23:28:14 by antoda-s          #+#    #+#             */
/*   Updated: 2024/04/04 00:50:12 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief 				Builds an error message string to be displayed and
///						frees the tokens list, cmds list and returns 1.
/// @param cmds 		Commands list
/// @param cmd_count 	Number of commands
/// @param tk 			Head of the token list
/// @return 			1
int	back_to_loop(t_command *cmds, int cmd_count, t_token **tk)
{
	show_func(__func__, FSTART, NULL);
	free_commands(cmds, cmd_count);
	free_tokens(tk);
	return (1);
}

/// @brief 		This function iterates through a linked list of tokens and
///				fills the command structure based on the type of token it
///				encounters.
/// @param tk	Head of the token list
/// @param cmd	Command structure
/// @param i	Index of the commands
/// @param j	Index of the arguments
/// @return		0 if success, 1 if failure
int	parse_commands(t_token *tk, t_command *cmd, int i, int j)
{
	show_func(__func__, FSTART, NULL);
	while (tk)
	{
		cmd[i].argv = ft_calloc((cmd[i].argc + 1), sizeof(char *));
		if (!cmd[i].argv)
			return (error_return("", errno, 1));
		j = 0;
		while (tk && tk->type != TK_PIPE)
		{
			if (tk->type == TK_NAME)
				cmd[i].argv[j++] = ft_strdup(tk->content);
			else if (tk->type == TK_I && redir(tk, &cmd[i].in))
				return (free_commands(cmd, i + 1));
			else if (tk->type == TK_O && redir(tk, &cmd[i].out))
				return (free_commands(cmd, i + 1));
			if (tk->type == TK_I || tk->type == TK_O)
				tk = tk->next;
			if (tk)
				tk = tk->next;
		}
		if (tk)
			tk = tk->next;
		cmd[i].argv[j] = NULL;
		i++;
	}
	return (SUCCESS);
}

/// @brief 				The script parser main function. All parsing starts here
/// @param s			The script pointer
/// @param line_buffer	The line buffer to parse
/// @return
int	parser(t_script *s, char **line_buffer)
{
	show_func(__func__, FSTART, NULL);
	t_token	*tk;

	tk = NULL;
	*line_buffer = readline("\001\033[1;94m\002minishell > \001\033[0m\002");
	if (!*line_buffer)
		*line_buffer = ft_strdup("exit");
	add_history(*line_buffer);
	if (tk_builder(line_buffer, &tk, s) == ERROR)
		return (free_tokens(&tk));
	tk_rm_blank(&tk);
	if (syntax_checker(tk))
		return (free_tokens(&tk));
	s->cmd_count = cmds_counter(tk);
	s->cmds = ft_calloc(s->cmd_count, sizeof(t_command));
	if (!s->cmds)
		return (error_return("", errno, 1));
	if (s->cmd_count == 0)
		return (back_to_loop(s->cmds, s->cmd_count, &tk));
	args_counter(tk, s);
	fnames_clear(s->cmds, s->cmd_count, tk);
	if (parse_commands(tk, s->cmds, 0, 0))
		return (free_tokens(&tk));
	free_tokens(&tk);
	return (SUCCESS);
}

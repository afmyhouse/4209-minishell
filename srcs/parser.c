/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 23:28:14 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/29 19:05:46 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/// @brief 			Checks if the number of arguments is valid
/// @param argc		Number of arguments
/// @return			SUCCESS if valid, ERROR if invalid
int	invalid_argc(int argc)
{
	show_func(__func__, MY_START);
	if (argc == 1)
	{
		printf("\t%s : Invalid number of arguments : %d\n", __func__, argc);
		return (show_func(__func__, ERROR));
	}
	else
	{
		printf("\t%s : Valid number of arguments:%d\n", __func__, argc);
	}
	return (show_func(__func__, SUCCESS));
}

/// @brief 			Checks if str has paired quotes and double quotes
/// @param str		String to parse
/// @param c		Character to check
/// @return
int	invalid_pair(char *str, char *c)
{
	int	i;
	int	k;

	show_func(__func__, MY_START);
	k = 0;
	if (!str || !c)
	{
		printf("\t%s : str or c == NULL\n", __func__);
		return (show_func(__func__, ERROR));
	}
	while (*c != '\0')
	{
		i = -1;
		while (str[++i] != '\0')
		{
			if (str[i] == *c)
				k++;
		}
		c++;
	}
	if (k % 2 != 0)
	{
		printf("\t%s : Invalid pairing : k(%c) = %d\n", __func__, *c, k);
		return (show_func(__func__, ERROR));
	}
	else
	{
		printf("\t%s : Valid quotes pairing\n", __func__);
		return (show_func(__func__, SUCCESS));
	}
}

/// @brief 				Checks if the quotes are valid
/// @param cmdline		Command line
/// @return				SUCCESS if valid, ERROR if invalid
int	invalid_quotes(char *line)
{
	show_func(__func__, MY_START);
	if (invalid_pair(line, "\"\'"))
		return (show_func(__func__, ERROR));
	return (show_func(__func__, SUCCESS));
}

/// @brief 			Checks if the argument is valid
/// @param argv		Argument
/// @return			SUCCESS if valid, ERROR if invalid
int	invalid_line(char *line)
{
	show_func(__func__, MY_START);
	if (line == NULL)
	{
		printf("\t%s : line  == NULL\n", __func__);
		return (show_func(__func__, ERROR));
	}
	else
	{
		printf("\t%s : line != NULL : %s\n", __func__, line);

		if (invalid_quotes(line))
			return (show_func(__func__, ERROR));
	}
	return (show_func(__func__, SUCCESS));
}

/**********************************************************************/
/**********************************************************************/
/**********************************************************************/
/**********************************************************************/
/**********************************************************************/

/// @brief 				Trims the token command from whitespaces
/// @param line_buffer	string input with script
/// @param head			pointer to the head of the token list
/// @param script		script structure
/// @return				SUCCESS if valid, ERROR if invalid
static int	tokenize(char **line, t_token **head, t_script *script)
{
	t_token	*tmp;
	char	*bis;

	if (!tokenizer(*line, head))
		//return (return_error("Syntax Error", 0));
		return (show_func(__func__, SYNTAX_ERROR));
	tmp = *head;
	while (tmp)
	{
		bis = tmp->content;
		tmp->content = replace_env_var(bis, script->envp, 0, 0);
		free(bis);
		tmp = tmp->next;
	}
	return (show_func(__func__, SUCCESS));
}

int	minishel_parser(t_script *script, char **line_buffer)
{
	t_token	*head;

	head = NULL;
	if (!line_buffer)
		return (show_func(__func__, ERROR));
	add_history(*line_buffer);
	if (tokenize(line_buffer, &head, script))
		return (free_tokens(&head));
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoffaux <sgoffaux@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 16:28:51 by mdeclerf          #+#    #+#             */
/*   Updated: 2021/10/08 14:44:24 by sgoffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	error_message_heredoc(char *content)
{
	ft_putstr_fd("Minishell: warning: here-document delimited", 2);
	ft_putstr_fd(" by end-of-file (wanted '", 2);
	ft_putstr_fd(content, 2);
	ft_putendl_fd("\')", 2);
}

/*
loop_heredoc(t_script *script, int pipe, int i) :
	This function reads the user's input until it finds the delimiters 
	set in heredoc linked list. It stores the input only for the last delimiter
	and places it in the pipe for later use as the input redirection.
*/
static void	loop_heredoc(t_list *h, int pipe)
{
	char	*tmp;
	char	*bis;

	bis = ft_strdup("");
	while (h)
	{
		tmp = readline("> ");
		if (!tmp || !ft_strncmp(tmp, h->content, ft_strlen(h->content) + 1))
		{
			if (!tmp)
				error_message_heredoc(h->content);
			h = h->next;
			free(tmp);
			continue ;
		}
		if (!h->next)
		{
			tmp = ft_strjoin_free(tmp, ft_strdup("\n"));
			bis = ft_strjoin_free(bis, tmp);
		}
		else
			free(tmp);
	}	
	write(pipe, bis, ft_strlen(bis));
	free(bis);
}

/*
heredoc(t_script *script, int i, char **path_env) :
	This function first initializes a pipe in which we can write the content
	that we'll read from the user.
*/
void	heredoc(t_script *script, int i, char **path_env)
{
	int		pipe_tmp[2];

	if (pipe(pipe_tmp) == -1)
	{
		write(2, "Error: pipe failed\n", 19);
		free_cmds_path(script, path_env);
		exit(1);
	}
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handler_heredoc);
	loop_heredoc(script->commands[i].in.heredoc, pipe_tmp[1]);
	if (pipe_tmp[0] != STDIN_FILENO)
	{
		if (dup2(pipe_tmp[0], STDIN_FILENO) == -1)
		{
			write(2, "Error: dup2 failed\n", 19);
			close_pipes(pipe_tmp, NULL);
			free_cmds_path(script, path_env);
			exit(1);
		}
	}
	close(pipe_tmp[0]);
	close(pipe_tmp[1]);
}

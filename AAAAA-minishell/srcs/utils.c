/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeclerf <mdeclerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 14:58:48 by sgoffaux          #+#    #+#             */
/*   Updated: 2021/10/08 13:09:07 by mdeclerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*replace_multiple_space(char *str)
{
	char	**split;
	char	*tmp;
	int		i;

	i = 0;
	split = ft_split_charset(str, " \t\v\r\f\n");
	tmp = malloc(sizeof(char) * ft_strlen(str));
	if (!tmp)
		return (str);
	while (split[i])
	{
		if (i > 0)
			tmp = ft_strjoin_free(tmp, ft_strdup(" "));
		tmp = ft_strjoin_free(tmp, split[i]);
		i++;
	}
	free(split);
	free(str);
	return (tmp);
}

/*
fill_heredoc(t_redirection *file):
	This function creates a node for the heredoc linked list with the file name 
	as the content and adds it to the back of the list.
*/
void	fill_heredoc(t_redirection *file)
{
	t_list	*tmp;

	tmp = ft_lstnew(ft_strdup(file->name));
	if (file->heredoc == NULL)
		file->heredoc = tmp;
	else
		ft_lstadd_back(&file->heredoc, tmp);
	file->flag = -1;
}

/*
return_error(const char *msg, int system):
	This function prints an error message to standard error.
*/
int	return_error(const char *msg, int system)
{
	ft_putstr_fd("Minishell: ", 2);
	if (system)
		perror(msg);
	else
		ft_putendl_fd(msg, 2);
	return (1);
}

/*
get_env_content(char *str, char **envp):
	This function iterates over the environment variables to find whether 
	or not the given variable (str) is defined and returns the content or 
	an empty freeable string. This function is also called in the builtin
	pwd to set the env var PWD to the current directory.
*/
char	*get_env_content(char *str, char **envp)
{
	char	*tmp;
	char	*ret;
	int		len;

	tmp = ft_strjoin(str, "=");
	len = ft_strlen(tmp);
	ret = NULL;
	while (*envp)
	{
		if (!ft_strncmp(tmp, *envp, len))
		{
			ret = ft_strdup(*envp + len);
			break ;
		}
		envp++;
	}
	free(tmp);
	if (!ret)
	{
		ret = ft_strdup("");
		if (!ret)
			return (NULL);
	}
	return (replace_multiple_space(ret));
}

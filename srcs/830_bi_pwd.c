/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   830_bi_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 23:46:04 by antoda-s          #+#    #+#             */
/*   Updated: 2024/02/10 00:34:19 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief 			Builtin pwd command
/// @param void		Builtin command arguments not required
/// @return			SUCCESS or ERROR
int	bi_pwd(t_script *s, int n)
{
	//show_func(__func__, MY_START, ft_strjoin("execute bi: ", "pwd"));
	char	*buf;

	(void) n;
	//env_var_setter("pwd", "_", &s->envp);
	buf = NULL;
	buf = getcwd(buf, MAX_PATH_LEN);
	if (!buf)
	{
		free(buf);
		buf = env_var_getter("PWD", s->envp, NULL);
		ft_putendl_fd(buf, STDOUT_FILENO);
	}
	else
		ft_putendl_fd(buf, STDOUT_FILENO);
	//show_func(__func__, SUCCESS, buf);
	free(buf);
	free_commands(s->cmds, 0);
	return (0);
}

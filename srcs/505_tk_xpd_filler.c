/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   505_tk_xpd_filler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 19:00:01 by antoda-s          #+#    #+#             */
/*   Updated: 2024/02/25 18:33:38 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @attention	>token builder< set of functions
/// @brief
/// @param ntk
/// @param s
/// @return
char	*tk_xpd_var_filler(char *ntk, t_script *s)
{
	int		i;
	char	*tmp;
	show_func(__func__, MY_START, NULL);

	i = 1;
	tmp = ntk;
	if (var_firstchar(ntk[i]) == SUCCESS)
	{
		show_func(__func__, SHOW_MSG, ft_strjoin("ntk[i] = ", ntk + 1));
		show_func(__func__, SHOW_MSG, (*s->envp));
		show_func(__func__, SHOW_MSG, (*s->envt));
		ntk = env_var_getter(ntk + 1, s->envp, s->envt);
		show_func(__func__, SHOW_MSG, "ready with env_var_getter");
	}
	else if (ft_isdigit(ntk[i]))
		ntk = ft_strdup("");
	else if (ntk[i] == '?' && g_exit_status >= 256)
		ntk = ft_itoa(WEXITSTATUS(g_exit_status));
	else if (ntk[i] == '?' && g_exit_status < 256)
		ntk = ft_itoa(g_exit_status);
	else if (ntk[i] == '$')
		ntk = ft_itoa(getpid());
	else
		ntk = ft_strdup(ntk + 1);
	free(tmp);
	show_func(__func__, SUCCESS, NULL);
	return (ntk);
}

/// @attention	>token builder< set of functions
/// @brief
/// @param ntk
/// @param s
/// @return
char	*tk_xpd_filler(char ***ntks, t_script *s)
{
	int		split;
	char	*tmp;
	show_func(__func__, MY_START, NULL);

	tmp = ft_strdup("");
	split = -1;
	while ((*ntks)[++split])
	{
		if ((*ntks)[split][0] == '$'
			&& ((*ntks)[split][1] || (*ntks)[split + 1]))
		{
			(*ntks)[split] = tk_xpd_var_filler((*ntks)[split], s);
			if (!(*ntks)[split])
				(*ntks)[split] = ft_strdup("");
		}
		else
			(*ntks)[split] = tk_xpd_unquote((*ntks)[split]);
		tmp = ft_strjoin_free(tmp, (*ntks)[split]);
	}
	return (tmp);
}

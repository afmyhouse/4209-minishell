/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   505_tk_xpd_filler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 19:00:01 by antoda-s          #+#    #+#             */
/*   Updated: 2024/02/10 00:13:06 by antoda-s         ###   ########.fr       */
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

	i = 1;
	tmp = ntk;
	if (var_firstchar(ntk[i]) == SUCCESS)
		ntk = env_var_getter(ntk + 1, s->envp, s->envt);
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

	tmp = ft_strdup("");
	split = -1;
	while ((*ntks)[++split])
	{
		if ((*ntks)[split][0] == '$'
			&& ((*ntks)[split][1] || (*ntks)[split + 1]))
				(*ntks)[split] = tk_xpd_var_filler((*ntks)[split], s);
		else
			(*ntks)[split] = tk_xpd_unquote((*ntks)[split]);
		tmp = ft_strjoin_free(tmp, (*ntks)[split]);
	}
	return (tmp);
}

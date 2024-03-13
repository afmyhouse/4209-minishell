/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   505_tk_xpd_filler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 19:00:01 by antoda-s          #+#    #+#             */
/*   Updated: 2024/03/13 16:42:05 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @attention		>token builder< set of functions
/// @brief 			PART 1: replaces var and removes quotes from a string
/// @param ntk 		array of strings to be processed
/// @param s 		struct with pparams to initialize
/// @return 		pointer to the newly created array
char	*tk_xpd_var_filler(char *ntk, t_script *s)
{
	show_func(__func__, MY_START, NULL);
	int		i;
	char	*tmp;

	i = 1;
	if (var_firstchar(ntk[i]) == SUCCESS)
		tmp = env_var_getter(ntk + 1, s->envp, s->envt);
	else if (ntk[i] == '0')
		tmp = ft_strdup("minishell");
	else if (ft_isdigit(ntk[i]))
		tmp = ft_strdup("");
	else if (ntk[i] == '?' && g_exit_status >= 256)
		tmp = ft_itoa(WEXITSTATUS(g_exit_status));
	else if (ntk[i] == '?' && g_exit_status < 256)
		tmp = ft_itoa(g_exit_status);
	else if (ntk[i] == '$')
		tmp = ft_itoa(getpid());
	else if (!ntk[i])
		tmp = ft_strdup("$");
	else
		tmp = ft_strdup(ntk);
	free(ntk);
	return (tmp);
}

/// @attention	>token builder< set of functions
/// @brief 		PART 1: replaces var and removes quotes from a string
/// @param ntk 	array of strings to be processed
/// @param s 	struct with pparams to initialize
/// @return 	pointer to the newly created array
char	*tk_xpd_filler(char ***ntks, t_script *s)
{
	show_func(__func__, MY_START, NULL);
	int		i;
	char	*tmp;
	char	*tmp2;

	tmp = ft_strdup("");
	i = -1;
	while ((*ntks)[++i])
	{
		tmp2 = (*ntks)[i];
		if ((*ntks)[i][0] == '$' && ((*ntks)[i][1] || (*ntks)[i + 1]))
		{
			(*ntks)[i] = tk_xpd_var_filler(tmp2, s);
			if (!(*ntks)[i])
				(*ntks)[i] = ft_strdup("");
		}/*******
		else if ((*ntks)[i][0] == '~' && !(*ntks)[i][1])
			(*ntks)[i] = env_var_getter("HOME", s->envp, s->envt);
		else********/
			(*ntks)[i] = tk_xpd_unquote(tmp2);
		tmp = ft_strjoin_free(tmp, (*ntks)[i]);
	}
	return (tmp);
}

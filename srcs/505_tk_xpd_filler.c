/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   505_tk_xpd_filler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 19:00:01 by antoda-s          #+#    #+#             */
/*   Updated: 2024/03/05 20:09:05 by antoda-s         ###   ########.fr       */
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
	// show_func(__func__, MY_START, NULL);
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
	// show_func(__func__, SUCCESS, NULL);
	// printf("%sALERT!! %s%s : dupped : address = %s%p%s\n", SBHRED, SRST, __func__, SHBLU, tmp, SRST);
	return (tmp);
}

/// @attention	>token builder< set of functions
/// @brief
/// @param ntk
/// @param s
/// @return
char	*tk_xpd_filler(char ***ntks, t_script *s)
{
	// show_func(__func__, MY_START, NULL);
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
		}
		else
			(*ntks)[i] = tk_xpd_unquote(tmp2);
		// printf("%sALERT!! %s%s : dupped : address = %s%p%s\n", SBHRED, SRST, __func__, SHBLU, (*ntks)[i], SRST);
		tmp = ft_strjoin_free(tmp, (*ntks)[i]);
		// printf("%sALERT!! %s%s : dupped : address = %s%p%s\n", SBHRED, SRST, __func__, SHBLU, (*ntks)[i], SRST);
		// printf("tmp = '%s'\n", tmp);
		// printf("nkts = '%s'\n", (*ntks)[i]);
	}
	// show_func(__func__, SUCCESS, NULL);
	return (tmp);
}
// char	*tk_xpd_filler(char ***ntks, t_script *s)
// {
// 	int		split;
// 	char	*tmp;
// 	show_func(__func__, MY_START, NULL);

// 	tmp = ft_strdup("");
// 	split = -1;
// 	while ((*ntks)[++split])
// 	{
// 		if ((*ntks)[split][0] == '$'
// 			&& ((*ntks)[split][1] || (*ntks)[split + 1]))
// 		{
// 			(*ntks)[split] = tk_xpd_var_filler((*ntks)[split], s);
// 			if (!(*ntks)[split])
// 				(*ntks)[split] = ft_strdup("");
// 		}
// 		else
// 			(*ntks)[split] = tk_xpd_unquote((*ntks)[split]);
// 		tmp = ft_strjoin_free(tmp, (*ntks)[split]);
// 	}
// 	return (tmp);
// }

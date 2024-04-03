/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   890_bi_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 00:14:30 by antoda-s          #+#    #+#             */
/*   Updated: 2024/04/04 00:52:06 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief 			get command arg <var>+=<vn> and built a bi_equal command arg
/// 				#1 if <var> does exists	  ->	<var>=<v1><v2>
///					#2 if <var> doesn't exist ->	<var>=<v2>
/// @param s 		Script structure with commans and args
/// @param n 		Index of command to be executed
/// @param i 		Index of argument to be checked
void	bi_append_new(t_script *s, int n, int i)
{
	show_func(__func__, FSTART, NULL);
	char	*var;
	char	*valn;
	char	*valo;

	var = ft_substr(s->cmds[n].argv[i], 0, ft_strlen(s->cmds[n].argv[i])
			- ft_strlen(ft_strchr(s->cmds[n].argv[i], '+')));
	valn = ft_strdup(ft_strchr(s->cmds[n].argv[i], '=') + 1);
	valo = env_var_getter(var, s->envp, s->envt);
	if (valo == NULL)
		valo = ft_strdup("");
	free(s->cmds[n].argv[i]);
	s->cmds[n].argv[i] = ft_strjoin_free(
			ft_strjoin_free(var, ft_strdup("=")),
			ft_strjoin_free(valo, valn));
}

/// @brief 			Looks for += embedded signs and call bi_append_new
/// @param s 		Script structure with commans and args
/// @param n 		Index of command to be executed
/// @return 		SUCCESS or ERROR
int	bi_append(t_script *s, int n, int i)
{
	show_func(__func__, FSTART, NULL);
	if (!s->envp || !s->cmds[n].argv[0])
		return (ERROR);
	while (s->cmds[n].argv[i])
	{
		if ((ft_strchr(s->cmds[n].argv[i], '+')
				&& ft_strchr(s->cmds[n].argv[i], '='))
			&& ((ft_strchr(s->cmds[n].argv[i], '=')
					- ft_strchr(s->cmds[n].argv[i], '+')) == 1))
			bi_append_new(s, n, i);
		i++;
	}
	return (SUCCESS);
}

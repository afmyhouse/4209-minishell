/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   845_bi_export_status.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 23:46:39 by antoda-s          #+#    #+#             */
/*   Updated: 2024/03/25 15:02:57 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief 		Export array method : ordered and declare statement
/// @param str 	Variable to be printed
void	export_print(char *str)
{
	char	*s1;
	char	*s2;

	if (!(str[0] == '_' && str[1] == '='))
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		if (!ft_strchr(str, '='))
			ft_putstr_fd(str, STDOUT_FILENO);
		else
		{
			s2 = ft_strjoin_free(ft_strdup(ft_strchr(str, '=') + 1),
					ft_strdup("\""));
			s1 = ft_strjoin_free(ft_substr(str, 0, ft_strlen(str)
						- ft_strlen(s2) + 1), ft_strdup("\""));
			ft_putstr_fd(s1, STDOUT_FILENO);
			ft_putstr_fd(s2, STDOUT_FILENO);
			ft_free(s1);
			ft_free(s2);
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
}

/// @brief 		Alphatecially ordered array
/// @param src 	Array to order
/// @return 	Ordered array
char	**ordered_array(char **d, char t, int n, int j)
{
	int	i;
	int	len_i;
	int	len_j;
	int	res_cmp;

	while (d[n] && d[n + 1])
	{
		j = n;
		i = j;
		while (d[++j])
		{
			len_i = ft_strchr(d[i], t) - d[i];
			len_j = ft_strchr(d[j], t) - d[j];
			res_cmp = ft_strncmp(d[i], d[j], ft_min(len_i, len_j));
			if (res_cmp > 0 || (res_cmp == 0 && len_i > len_j))
				i = j;
		}
		ft_strswap(&d[n++], &d[i]);
	}
	return (d);
}

/// @brief 		Export the environment variables
/// @param s 	Script structure with commans and args
/// @param n 	Index of command to be executed
/// @return 	SUCCESS or ERROR
int	export_status(t_script *s, int n)
{
	int		i;
	char	**order;

	if (!s->cmds[n].argv[1])
	{
		if (!s->envp)
			return (1);
		order = envp_init(s->envp);
		order = ordered_array(order, '=', 0, 0);
		i = -1;
		while (order[++i])
			export_print(order[i]);
		free_array(order, 0);
	}
	else if (s->cmds[n].argv[1][0] == '\0')
		return (error_return("Syntax error", 1, 2));
	return (SUCCESS);
}

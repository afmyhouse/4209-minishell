/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   610_env_getter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 19:00:01 by antoda-s          #+#    #+#             */
/*   Updated: 2024/03/19 00:04:03 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief		This function iterates over the environment variables to
///				find whether or not the given variable (str) is defined and
///				returns the content or an empty freeable string.
/// @param var	Variable to be found
/// @param envp	Environment variables
/// @return		Content of the variable
char	*envx_var_getter(char *var, char **envx)
{
	char	*tmp;
	char	*ret;
	int		len;

	if (!envx || !var)
		return (NULL);
	tmp = ft_strjoin(var, "=");
	len = ft_strlen(tmp);
	ret = NULL;
	while (*envx)
	{
		if (!ft_strncmp(tmp, *envx, len))
		{
			ret = ft_strdup(*envx + len);
			break ;
		}
		envx++;
	}
	free(tmp);
	return (ret);
}

/// @brief		This function iterates over the environment variables to
///				find whether or not the given variable (str) is defined and
///				returns the content or an empty freeable string.
/// @param var	Variable to be found
/// @param envp	Environment variables
/// @return		Content of the variable
char	*env_var_getter(char *var, char **envp, char **envt)
{
	char	*ret;

	ret = envx_var_getter(var, envp);
	if (!ret)
		ret = envx_var_getter(var, envt);
	return (ret);
}

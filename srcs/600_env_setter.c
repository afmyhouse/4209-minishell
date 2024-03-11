/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   600_env_setter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 19:00:01 by antoda-s          #+#    #+#             */
/*   Updated: 2024/03/10 23:51:58 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief 			This function deletes an environment variable and returns a
///					new malloced array without the deleted variable
/// @param del		Variable name string to be deleted
/// @param envx		Environment variables array
/// @param j 		Starting index to browse the array
/// @return			Updated environment variables
char	**env_del_one(char *del, char **envx, int j)
{
	show_func(__func__, MY_START, NULL);
	char	**new_array;
	char	*tmp;
	int		i;

	i = 0;
	while ((envx)[i])
		i++;
	new_array = ft_calloc(i, sizeof(char *));
	if (!new_array)
	{
		(return_error("", errno, 1));
		return (NULL);
	}
	i = -1;
	while (envx[++i])
	{
		tmp = ft_substr((envx)[i], 0, ft_strlen((envx)[i])
				- ft_strlen(ft_strchr((envx)[i], '=')));
		if (ft_strncmp(tmp, del, ft_max(ft_strlen(del), ft_strlen(tmp))))
			new_array[j++] = ft_strdup((envx)[i]);
		free(tmp);
	}
	new_array[j] = NULL;
	free_array(envx, 0);
	return (new_array);
}

/// @brief 			This function adds a new environment variable and returns a
///					new malloced array with the new variable included
/// @param envx		OLD Environment variables array
/// @param	new		NEW variable to be added
/// @return			Updated environment variables
char	**env_add_one(char **envx, char *new)
{
	show_func(__func__, MY_START, NULL);
	char	**new_array;
	int		i;

	i = 0;
	while ((envx)[i])
		i++;
	i = i + 2;
	new_array = ft_calloc(i, sizeof(char *));
	if (!new_array)
	{
		return_error("", errno, 1);
		return (NULL);
	}
	i = -1;
	while (envx[++i])
		new_array[i] = ft_strdup(envx[i]);
	new_array[i] = new;
	new_array[++i] = NULL;
	free_array(envx, 0);
	return (new_array);
}

/// @brief 			This function gets the environment variable index
/// @param var 		variable to be found
/// @param envp 	Environment variables
/// @return			Index of the variable
int	env_var_index_getter(char *var, char **envx)
{
	show_func(__func__, MY_START, NULL);
	int	i;

	if (!envx)
		return (-1);
	i = -1;
	while (envx[++i])
	{
		if ((ft_strncmp(var, envx[i], ft_strlen(var)) == SUCCESS)
			&& (envx[i][ft_strlen(var)] == '='
			|| envx[i][ft_strlen(var)] == '\0'))
			return (i);
	}
	return (-1);
}

/// @brief 				This function sets the environment variable
/// @param val 			Value to be set
/// @param var 			Variable to be set
/// @param envp 		Environment variables
/// @return 			0 if success, -1 if error
int	env_var_setter(char *val, char *var, char ***envx)
{
	show_func(__func__, MY_START, NULL);
	int		i;
	char	*var_new;

	if (!*envx)
		return (-1);
	if (val)
		var_new = ft_strjoin_free(ft_strjoin(var, "="), ft_strdup(val));
	else
		var_new = ft_strdup(var);
	i = env_var_index_getter(var, *envx);
	if (i == -1)
		*envx = env_add_one(*envx, var_new);
	else
	{
		if (ft_strncmp(var_new, (*envx)[i],
			ft_max(ft_strlen((*envx)[i]), ft_strlen(var_new))) != SUCCESS)
			ft_strswap(&var_new, &(*envx)[i]);
		free(var_new);
	}
	return (SUCCESS);
}

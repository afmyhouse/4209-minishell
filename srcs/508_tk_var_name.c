/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   508_tk_var_name.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:10:37 by antoda-s          #+#    #+#             */
/*   Updated: 2024/04/04 00:50:44 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @attention	>token builder< set of functions
/// @brief		checks if char is a valid identifier char ('_', alpha, digit)
/// @param c 	char to be checked
/// @return		SUCCESS or ERROR
int	var_name_checker(char c)
{
	show_func(__func__, FSTART, NULL);
	if (ft_isalnum(c) || c == '_')
		return (SUCCESS);
	return (ERROR);
}

/// @attention	>token builder< set of functions
/// @brief		checks if char is a valid 1st identifier char ('_' or alpha)
/// @param c 	char to be checked
/// @return		SUCCESS or ERROR
int	var_firstchar(char c)
{
	show_func(__func__, FSTART, NULL);
	if (ft_isalpha(c) || c == '_')
		return (SUCCESS);
	return (ERROR);
}

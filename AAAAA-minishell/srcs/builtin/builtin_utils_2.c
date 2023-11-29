/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeclerf <mdeclerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 14:48:16 by mdeclerf          #+#    #+#             */
/*   Updated: 2021/10/07 17:16:47 by mdeclerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
error_message_export(char *message) : 
	Called by builtin_export(t_script *script, t_command cmd)
*/
void	error_message_export(char *message)
{
	ft_putstr_fd("Minishell: export: '", 2);
	ft_putstr_fd(message, 2);
	ft_putendl_fd("': not a valid identifier", 2);
}

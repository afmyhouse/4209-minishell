/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   799_exec_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 23:43:45 by antoda-s          #+#    #+#             */
/*   Updated: 2024/03/22 21:53:07 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief 		displays error message on fork error
/// @param path	array to free
/// @return		status
int	fork_error(char **path)
{
	write(2, "Error: fork failed\n", 19);
	g_exit_status = 1;
	return (free_array(path, ERROR));
}

/// @brief 		displays error message on pipe error
/// @param path	array to free
/// @return		status
int	pipe_error(char **path)
{
	write(2, "Error: pipe failed\n", 19);
	g_exit_status = 1;
	return (free_array(path, ERROR));
}

/// @brief 			Shows error and program sourcing it and exit(1) freeing
/// 				allocated vars
/// @param msg 		Message to show
/// @param errms 	Error message
/// @param s 		Script to be freed
/// @param path 	Path to be freed
void	exit_forks(char *msg, int errms, t_script *s)
{
	return_error(msg, errms, 1);
	free_exit(s, 1);
	exit(1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   799_exec_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 23:43:45 by antoda-s          #+#    #+#             */
/*   Updated: 2024/03/05 21:26:46 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fork_error(char **path)
{
	// show_func(__func__, MY_START, NULL);
	write(2, "Error: fork failed\n", 19);
	g_exit_status = 1;
	// free_array_name(path, "path");
	free_array(path);
	// free_array_name(path, "path");
	return (1);
}

int	pipe_error(char **path)
{
	// show_func(__func__, MY_START, NULL);
	write(2, "Error: pipe failed\n", 19);
	g_exit_status = 1;
	free_array(path);
	// free_array_name(path, "path");
	return (1);
}

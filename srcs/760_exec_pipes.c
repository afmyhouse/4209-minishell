/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   760_exec_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:26:05 by antoda-s          #+#    #+#             */
/*   Updated: 2024/03/10 23:45:42 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//// @brief 		This function initializes pipes needed to redirect the
///					output of the previous cmd into the next one.
/// 				It initializes a pipe for the next result of a command and
/// @param path 	Commands execution path
/// @param pipe1 	Pointer to the pipe to read previous data
/// @param pipe2 	Pointer to the pipe to write results
/// @return 		Pointer to the pipes array x 2 pipes
int	**pipe_init(char **path, int *pipe1, int *pipe2)
{
	show_func(__func__, MY_START, NULL);
	int	**pipes;

	pipes = malloc(sizeof(int *) * 2);
	if (!pipes)
		return (NULL);
	if (pipe(pipe2) == -1)
	{
		pipe_error(path);
		return (NULL);
	}
	pipes[0] = pipe1;
	pipes[1] = pipe2;
	return (pipes);
}

/// @brief 		This fucntion is usefull to manage the closing of pipes as long
/// 			they are not nedeed. It called when a child process is done with
/// 			its pipe (previous) or whenever there are errors creating
///				or the dup2 of fd fails.
/// @param pa 	pipa a, initial pipe of an odd cmd i (in a list from 1 to n-1)
/// @param pb 	pipe b, initial pipe of an even cmd i (in a list from 1 to n-1)
void	pipe_closer(int *pa, int *pb)
{
	show_func(__func__, MY_START, NULL);
	if (pa)
	{
		close(pa[0]);
		close(pa[1]);
	}
	if (pb)
	{
		close(pb[0]);
		close(pb[1]);
	}
}

/// @brief 			This function is called every time we have to dup2 a pipe.
/// 				It takes the pipe, and the extremity we have to dup and
///					replace it with the corresponding STDIN/STDOUT.
/// @param pipe 	The pipe to dup.
/// @param end 		The extremity we have to dup.
/// @return
int	pipe_std_setter(int *pipe, int end)
{
	show_func(__func__, MY_START, NULL);
	if (pipe[end] != end)
		return (dup2(pipe[end], end));
	return (SUCCESS);
}

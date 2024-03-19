/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   720_exec_many.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:26:05 by antoda-s          #+#    #+#             */
/*   Updated: 2024/03/19 11:45:12 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief 			Executes the first command in a pipped script
/// @param s 		Script contents and parameters including redirect info
/// @param path 	Commands execution path
/// @param pipeout 	Pointer to the pipe to output result
/// @return 		SUCCESS or ERROR
int	exec_cmd_1(t_script *s, char **path, int *pipeout)
{
	int	pid;

	(void) path;
	if (pipe(pipeout) == -1)
	{
		free (s->path);
		return (return_error("", errno, 1));
	}
	pid = fork();
	if (pid == -1)
	{
		free (s->path);
		return (return_error("", errno, 1));
	}
	if (pid == 0)
		ex_child_1(s, pipeout);
	close(pipeout[1]);
	return (SUCCESS);
}

/// @brief 			Executes the command > 1 anmd < n in a pipped script
/// @param s 		Script contents and parameters including redirect info
/// @param path 	Commands execution path
/// @param pipes 	Pointer to the pipes array x 2 pipes
///					one pipe to read previous data, another to write results
/// @param pid 		NOTHING
int	exec_cmd_i(t_script *s, char **path, int **pipes, int i)
{
	int	pid;

	(void) path;
	if (!pipes)
		return (return_error("", errno, 1));
	pid = fork();
	if (pid == -1)
	{
		free(s->path);
		return (return_error("", errno, 1));
	}
	if (pid == 0)
		ex_child_i(s, pipes, i);
	close(pipes[0][0]);
	close(pipes[1][1]);
	free(pipes);
	return (SUCCESS);
}

/// @brief 			Executes the last command in a pipped script
/// @param s 		Script contents and parameters including redirect info
/// @param path 	Commands execution path
/// @param pipein 	Pointer to the pipe with input data, resulted from previous
/// @param pid 		NOTHING
int	exec_cmd_n(t_script *s, int *pipein)
{
	int	i;
	int	pid;

	i = s->cmd_count - 1;
	pid = fork();
	if (pid == -1)
	{
		free (s->path);
		return (return_error("", errno, 1));
	}
	if (pid == 0)
		ex_child_n(s, pipein, i);
	pipe_closer(pipein, NULL);
	return (free_array(s->path, SUCCESS));
}

/// @brief 			Selects the pipe for each inbetween command "i" and calls
/// 				the function to execute the command "i".
/// @param s 		Script contents and parameters including redirect info
/// @param path 	Commands execution path
/// @param pipe1 	Pointer to the first pipe
/// @param pipe2 	Pointer to the second pipe
/// @return 		SUCCESS or ERROR
int	exec_cmd_loop(t_script *s, char **path, int *pipe1, int *pipe2)
{
	int	i;
	int	cmd_idx;
	int	**pipes;

	(void) path;
	i = 0;
	cmd_idx = 0;
	while (++i < s->cmd_count - 1)
	{
		if (cmd_idx % 2 == 0)
		{
			pipes = pipe_init(s->path, pipe1, pipe2);
			if (exec_cmd_i(s, s->path, pipes, i) == 1)
				return (-1);
		}
		else
		{
			pipes = pipe_init(s->path, pipe2, pipe1);
			if (exec_cmd_i(s, s->path, pipes, i) == 1)
				return (-1);
		}
		cmd_idx++;
	}
	return (cmd_idx);
}

/// @brief 			Executes a script with multiple commands. The function will
/// 				fork to execute each command and will call the necessary
/// 				functions required too redirect pipes, files. The parent
/// 				waiting is performed here and will treat the exit status of
/// 				the child processes.
/// @param s 		Script contents and parameters including redirect info
/// @param path 	Commands execution path
/// @return 		SUCCESS or ERROR
// int	exec_many(t_script *s, char **path)
int	exec_many(t_script *s)
{
	int	pipe1[2];
	int	pipe2[2];
	int	cmd;

	//(void) path;
	signal_setter_fork();
	if (exec_cmd_1(s, s->path, pipe1) == 1)
		return (ERROR);
	cmd = exec_cmd_loop(s, s->path, pipe1, pipe2);
	if (cmd == -1)
		return (ERROR);
	if (cmd % 2 == 1 && exec_cmd_n(s, pipe2) == 1)
		return (1);
	else if (cmd % 2 == 0 && exec_cmd_n(s, pipe1) == 1)
		return (ERROR);
	wait(&g_exit_status);
	while (cmd-- > 0)
		wait(&g_exit_status);
	wait(&g_exit_status);
	if (WIFSIGNALED(g_exit_status))
		g_exit_status = 128 + WTERMSIG(g_exit_status);
	else if (WIFEXITED(g_exit_status))
		g_exit_status = WEXITSTATUS(g_exit_status);
	return (SUCCESS);
}

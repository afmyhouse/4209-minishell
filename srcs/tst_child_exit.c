/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tst_child_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 20:05:44 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/30 20:15:27 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <sys/wait.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

int	main(void)
{
	pid_t							child_pid;
	pid_t							rc_pid;
	int								chld_state;
	// tpf_create_process_parameters_t	create_parameters;

	child_pid = fork();
	printf("STARTED\n");
	if (child_pid == 0)
	{
		sleep(5);
		exit(2);
	}
	rc_pid = wait(&chld_state);
	if (rc_pid > 0 && child_pid != 0)
	{
		if (WIFEXITED(chld_state))
			printf("Child exited with RC = %d\n", WEXITSTATUS(chld_state));
		if (WIFSIGNALED(chld_state))
			printf("Child exited via signal %d\n", WTERMSIG(chld_state));
	}
	else
	{
		if (errno == ECHILD)
			printf("No children exist.\n");
		else
		{
			printf("Unexpected error.\n");
			abort();
		}
	}
}

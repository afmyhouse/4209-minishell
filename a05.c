/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f03.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 13:11:26 by antoda-s          #+#    #+#             */
/*   Updated: 2023/12/14 17:32:33 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



//int args = s->commands.argc; 
//int child_pids[args];
//int pipes[args + 1][2];
int i = -1;


while (++i < args)
{
	if (pipe(pipes(i)) == -1)
	{
		printf("erro criar pipes\n");
		return (2);

	}
}

i = -1;
while (++i < args)
{
	child_pids[i] = fork();
	if (child_pids[i] == -1)
	{
		printf("erro ao criar processos\n");
		return (2);
	}
	if (child_pids[i] == 0) 
	{
		// child process
		int j = -1;

		while(++j < args)
		{
			if (i != j)
				close(pipes[j][0]);
			if (i + 1 != j)
				close (pipes[j][1]);
		}

		// executar commando

		close(pipes[i][0]);
		close (pipes[i + 1][1]);
	}

	//main process
	int j = -1;

	while(++i < args)
	{
		if (i != args)
			close(pipes[i][0]);
		if (i != 0)
			close (pipes[i][1]);
	}


	i = -1;
	while (++i < args)
		wait(NULL);
}






/*teste de merge branch*/
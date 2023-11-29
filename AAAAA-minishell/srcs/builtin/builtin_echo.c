/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeclerf <mdeclerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 14:55:52 by mdeclerf          #+#    #+#             */
/*   Updated: 2021/10/07 16:24:08 by mdeclerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
flag_handling(t_command command, int *flag, int *i) :
	This function handles the flag -n of echo. It checks if the flag is only
	composed of allowed letters and increments i which iterates through the
	argv. It also increments flag which is used to detectif a final \n is
	needed.
*/
static int	flag_handling(t_command command, int *flag, int *i)
{
	size_t	j;

	j = 2;
	while (command.argv[*i][j] == 'n' || command.argv[*i][j] == 'e'
		|| command.argv[*i][j] == 'E')
		j++;
	if (j == ft_strlen(command.argv[*i]))
	{
		(*i)++;
		(*flag)++;
	}
	else
		return (0);
	return (1);
}

static int	echo_print(t_command command, int i)
{
	write(1, command.argv[i], ft_strlen(command.argv[i]));
	if (i != command.argc - 1)
		write(1, " ", 1);
	i++;
	return (i);
}

int	builtin_echo(t_command command)
{
	int		i;
	int		flag;

	i = 1;
	flag = 0;
	if (!command.argv[1])
	{
		write(1, "\n", 1);
		return (0);
	}
	while (command.argv[i] && command.argv[i][0] == '-'
		&& command.argv[i][1] == 'n')
	{
		if (!flag_handling(command, &flag, &i))
			break ;
	}
	if (!command.argv[i])
		return (0);
	while (command.argv[i])
		i = echo_print(command, i);
	if (flag == 0)
		write(1, "\n", 1);
	return (0);
}

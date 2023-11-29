/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:26:48 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/29 12:28:30 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_envp(char **my_envp)
{
	int	i;

	i = 0;
	while (my_envp[i])
	{
		free(my_envp[i]);
		i++;
	}
	free(my_envp);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 17:52:21 by rvan-aud          #+#    #+#             */
/*   Updated: 2021/10/07 16:34:20 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
odd_before/odd_after(char **str, int i, char c):
	These two functions return 1 if the number of the given quotation marks 
	before or after the index is odd, and returns 0 if even.
*/
int	odd_before(char **str, int i, char c)
{
	int	count;
	int	j;

	count = 0;
	while (i--)
	{
		j = 0;
		while (str[i] && str[i][j])
		{
			if (str[i][j] == c)
				count++;
			j++;
		}
	}
	return (count % 2);
}

int	odd_after(char **str, int i, char c)
{
	int	count;
	int	j;

	count = 0;
	while (str[i])
	{
		j = 0;
		while (str[i] && str[i][j])
		{
			if (str[i][j] == c)
				count++;
			j++;
		}
		i++;
	}
	return (count % 2);
}

/*
free_split(char **split):
	This function simply frees the content of the split string.
*/
void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

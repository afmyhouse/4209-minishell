/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trimmer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 23:11:39 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/29 00:23:18 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/// @brief 				Trims the token command from whitespaces
/// @param token		Token to be trimmed
/// @param trimmer		Trimmer characters " \t\v\r\n\f"
// static void	trimmer(t_token *token, char *trimmer)
// {
// 	while (token)
// 	{
// 		token->cmd = ft_strtrim_free(token->cmd, trimmer);
// 		token = token->next;
// 	}
// }
char	*trimmer(char *line, const char *trimmer)
{
	show_func(__func__, MY_START);
	printf("\tline = %s : trimmer = |%s|\n", line, trimmer);
	if (line)
		return (ft_strtrim_free(line, trimmer));
	return (NULL);
}

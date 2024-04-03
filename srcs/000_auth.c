/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   000_auth.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 22:41:09 by antoda-s          #+#    #+#             */
/*   Updated: 2024/04/03 23:57:38 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bi_help(void)
{
	ft_putstr_fd("\n\
/* ************************************************************************** */\n\
/*                                                                            */\n\
/*   This is a restricted shell. A mini version of bash.                      */\n\
/*                                                                            */\n\
/*   Try out some of the basic functions of bash such as:                     */\n\
/*    > ls, cd, grep, cat, touch, echo, pwd, export,                          */\n\
/*    > unset, env, etc...                                                    */\n\
/*    > variables ( new and append )                                          */\n\
/*    > heredoc, and redirections ( <, >, >>).                                */\n\
/*                                                                            */\n\
/*   Here are some prompt examples you may try :                              */\n\
/*    > ls -lpR | grep / | wc -l                                              */\n\
/*    > cat < file.txt | grep -i 'hello' > newfile.txt                        */\n\
/*    > var=\"ho ok\"                                                           */\n\
/*    > ec$var                                                                */\n\
/*    > echo \"X'$HOME \"$$\"HONOR\"07\"$4$AB$CD EF\"NEW\"OT'TO\"'NOT$A'              */\n\
/*                                                                            */\n\
/*   Type 'help' to display this screen.                                      */\n\
/*   Type 'exit' or ctrl+d to leave.                                          */\n\
/*   Type 'authors' to get info about authors                                 */\n\
/*                                                                            */\n\
/* ************************************************************************** */\n\
\n", 2);
	return (0);
}

int	bi_auth(void)
{
	ft_putstr_fd("\n\
/* ************************************************************************** */\n\
/*                                                                            */\n\
/*   This is 'minishell', a mini version of bash          :::      ::::::::   */\n\
/*   created at 42 School PORTO, during the             :+:      :+:    :+:   */\n\
/*   'common-core' cursus                             +:+ +:+         +:+     */\n\
/*   By:                                            +#+  +:+       +#+        */\n\
/*   antoda-s <antoda-s@student.42porto.com>      +#+#+#+#+#+   +#+           */\n\
/*   fpinho-d <fpinho-d@student.42porto.com>           #+#    #+#             */\n\
/*   2024/03                                          ###   ########.fr       */\n\
/*                                                                            */\n\
/* ************************************************************************** */\n\
\n", 2);
	return (0);
}

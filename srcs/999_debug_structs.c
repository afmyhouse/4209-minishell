/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   999_debug_structs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 23:29:02 by antoda-s          #+#    #+#             */
/*   Updated: 2024/04/04 00:52:22 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//#include "../include/minishell.h"
void	execute_show(t_script *s)
{
	show_func(__func__, FSTART, NULL);
	int	i;
	int	j;

	i = -1;
	j = -1;
	if (!s || !DEBUG_ARRAY)
		return ;
	// show_func(__func__, MY_START, NULL);
	printf("%s**********************************************************%s\n", SBHGRN, SRST);
	printf("%s(->)  s->com_count: \t%i\n", SBHYLW, s->cmd_count);
	while (++j < s->cmd_count)
	{
		printf("%s(->)  s->cmds[%d]. %s\n", SBHYLW, j, SRST);
		//printf("%s(->)  \t.cmd \t\t%s%s\n", SBHYLW, s->cmds[j].cmd, SRST);
		printf("%s(->)  \t.argc : \t%s%d\n", SBHYLW, SBHGRN, s->cmds[j].argc);
		while (++i < s->cmds[j].argc)
		{
			if (i == 0)
				printf("%s(->)  \t.argv[%d]: \t%s%s\n", SBHYLW, i, SBHGRN, s->cmds[j].argv[i]);
			else
				printf("%s(->)  \t.argv[%d]: \t%s%s\n", SBHYLW, i, SBHWHT, s->cmds[j].argv[i]);
		}
		printf("%s(->)  \t.out.name: \t%s%s\n", SBHYLW, SBHCYN, s->cmds[j].out.name);
		printf("%s(->)  \t.out.flag: \t%s%d\n", SBHYLW, SBHCYN, s->cmds[j].out.flag);
		printf("%s(->)  \t.out->heredoc: \t%s%p\n", SBHYLW, SBHCYN,s->cmds[j].out.heredoc);
		printf("%s(->)  \t.in.name: \t%s%s\n", SBHYLW, SBHBLU, s->cmds[j].in.name);
		printf("%s(->)  \t.in.flag: \t%s%d\n", SBHYLW, SBHBLU, s->cmds[j].in.flag);
		printf("%s(->)  \t.in->heredoc: \t%s%p%s\n", SBHYLW, SBHBLU,s->cmds[j].in.heredoc, SRST);
		i = -1;
		printf("%s**********************************************************\n*%s\n", SBHGRN, SRST);
	}
	//show_func(__func__, SUCCESS, NULL);
	return ;
}

/// @brief 				This function prints the environment variables
/// @param envp			Environment variables
/// @return				void
void	show_array(char **envx, const char *name)
{
	show_func(__func__, FSTART, NULL);
	int	i;

	i = 0;
	show_pointer(__func__, FSTART, name, (envx));
	if (!envx || !DEBUG_ARRAY)
		return ;
	while (envx[i])
	{
		printf("%s : %s%p%s : %p : %s[%i] = %s%s\n", __func__, SHGRN,
			envx + i, SHBLU, envx[i], name, i, envx[i], SRST);
		i++;
	}
	printf("%s : %s%p%s : %p : %s[%i] = %s%s\n", __func__, SHGRN,
		envx + i, SHBLU, envx[i], name, i, envx[i], SRST);
	show_func(__func__, SUCCESS, NULL);
}

void	show_token_list(t_token *token)
{
	show_func(__func__, FSTART, NULL);
	t_token	*tk_ptr;

	tk_ptr = token;
	if (!tk_ptr || !DEBUG_ARRAY)
		return ;
	printf("%s*********************************************************%s\n",
		SBHGRN, SRST);
	while (tk_ptr)
	{
		printf("%s%p%s\n", SBHYLW, tk_ptr, SRST);
		printf("%s-> token->content = '%s%s%s'%s\n",
			SBHPPL, SBWHT, tk_ptr->content, SBHPPL, SRST);
		printf("%s-> token->size = '%s%d%s'%s\n",
			SBHPPL, SBWHT, tk_ptr->size, SBHPPL, SRST);
		printf("%s-> token->type = '%s%d%s'%s\n",
			SBHPPL, SBWHT, tk_ptr->type, SBHPPL, SRST);
		printf("%s*********************************************************%s\n",
			SBHGRN, SRST);
		tk_ptr = tk_ptr->next;
	}
}

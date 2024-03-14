/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   999_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 23:29:02 by antoda-s          #+#    #+#             */
/*   Updated: 2024/03/14 17:17:42 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//#include "../include/minishell.h"
void	execute_show(t_script *s)
{
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

void	show_func_msg(const char *msg)
{
	if (DEBUG_ALL)
	{
		if (!msg)
			write(STDERR_FILENO, "\n", 1);
		else
		{
			write(STDERR_FILENO, "-> ", 3);
			write(STDERR_FILENO, msg, ft_strlen(msg));
			write(STDERR_FILENO, "\n", 1);
		}
	}
}

/// @brief 				Shows the function name and status
/// @param func_name	Name of the function
/// @param status		Status of the function
/// @return				Status of the function
int show_func(const char *func_name, int status, char *msg)
{
	int					i;
	const t_debug_msg	debug_msg[14] = {
	{" INFO", SHOW_MSG, 5, "(ii) ", SBHPPL},
	{" START", MY_START, 6, "(>>) ", SHBLU},
	{" ERROR", ERROR, 6, "(xx) ", SHRED},
	{" SUCCESS", SUCCESS, 8, "(xx) ", SHGRN},
	{" MALLOC", D_MALLOC, 7, "(**) ", SBHRED},
	{" FREE", D_FREE, 5, "(**) ", SBHRED},
	{" MALLOC_ERROR", MALLOC_ERROR, 13, "(xx) ", SBHRED},
	{" MALLOC_NOT_ALLOC", MALLOC_NOT_ALLOCATED, 18, "(xx) ", SBHCYN},
	{" FILE_ERROR", FILE_ERROR, 11, "(xx) ", SBHRED},
	{" CHILD_EXIT", CHILD_EXIT, 11, "(xx) ", SBHYLW},
	{" EXIT_FAILURE", EXIT_FAILURE, 14, "(xx) ", SBHRED},
	{" FILE_NOT_FOUND", FILE_NOT_FOUND, 16, "(xx) ", SBHRED},
	{" FILE_NOT_DELETED", FILE_NOT_DELETED, 17, "(xx) ", SBHRED},
	{NULL, 0, 0, NULL, NULL}};

	if (DEBUG_ALL)
	{
		i = -1;
		while (debug_msg[++i].status != status && debug_msg[i].msg)
		{
			if (debug_msg[i].status == status)
				break ;
		}
		if (DEBUG_COLOR)
		{
			printf("%s%s%s%s%s%s%s", SBHWHT, debug_msg[i].msg_header, SBWHT, func_name,
				debug_msg[i].color, debug_msg[i].msg, SRST);
			if (msg)
				printf("%s-> %s%s\n", SBHCYN, msg, SRST);
			else
				printf("%s\n", SRST);
		}
		else
		{
			write(STDERR_FILENO, debug_msg[i].msg_header, 5);
			write(STDERR_FILENO, func_name, ft_strlen(func_name));
			write(STDERR_FILENO, debug_msg[i].msg, debug_msg[i].len);
			show_func_msg(msg);
		}
		// printf("\n");
	}
	else if (DEBUG_FREE && (status == D_FREE || status == D_MALLOC))
	{
		i = -1;
		while (debug_msg[++i].status != status && debug_msg[i].msg)
		{
			if (debug_msg[i].status == status)
				break ;
		}
		if (DEBUG_COLOR)
		{
			printf("%s%s%s%s%s%s%s", SBHWHT, debug_msg[i].msg_header, SBWHT, func_name,
				debug_msg[i].color, debug_msg[i].msg, SRST);
			if (msg)
				printf("%s-> %s%s\n", SBHCYN, msg, SRST);
			else
				printf("%s\n", SRST);
		}
		else
		{
			write(STDERR_FILENO, debug_msg[i].msg_header, 5);
			write(STDERR_FILENO, func_name, ft_strlen(func_name));
			write(STDERR_FILENO, debug_msg[i].msg, debug_msg[i].len);
			show_func_msg(msg);
		}
		// printf("\n");
	}
	ft_free(msg);
	return (status);
}

/// @brief 				This function prints the environment variables
/// @param envp			Environment variables
/// @return				void
void	show_array(char **envx, const char *name)
{
	show_pointer(__func__, MY_START, name, (envx));
	int i = 0;

	if (!envx || !DEBUG_ARRAY)
		return ;
	while (envx[i])
	{
		printf("%s : %s%p%s : %p : %s[%i] = %s%s\n", __func__, SHGRN, envx + i, SHBLU, envx[i], name, i, envx[i], SRST);
		i++;
	}
	printf("%s : %s%p%s : %p : %s[%i] = %s%s\n", __func__, SHGRN, envx + i, SHBLU, envx[i], name, i, envx[i], SRST);
	// show_func(__func__, SUCCESS, NULL);
}

void show_token_list(t_token *token)
{
	t_token *tk_ptr;

	tk_ptr = token;
	if (!tk_ptr || !DEBUG_ARRAY)
		return ;
	ft_printf("%s**********************************************************%s\n", SBHGRN, SRST);
	while (tk_ptr)
	{
		ft_printf("%s%p%s\n", SBHYLW, tk_ptr, SRST);
		ft_printf("%s-> token->content = '%s%s%s'%s\n",
			SBHPPL, SBWHT, tk_ptr->content, SBHPPL, SRST);
		ft_printf("%s-> token->size = '%s%d%s'%s\n",
			SBHPPL, SBWHT, tk_ptr->size, SBHPPL, SRST);
		ft_printf("%s-> token->type = '%s%d%s'%s\n",
			SBHPPL, SBWHT, tk_ptr->type, SBHPPL, SRST);
		ft_printf("%s**********************************************************%s\n", SBHGRN, SRST);
		tk_ptr = tk_ptr->next;
	}
}

char	*ft_var_address(const char *varname, void *var)
{
	char	*ret;

	ret = ft_strjoin_free(ft_strjoin(varname, " -> "), ft_itoa_base((unsigned long)var, 'x'));
	return (ret);
}

void	show_pointer(const char *func, int status, const char *msg, void *ptr)
{
	char	*tmp;

	if (!DEBUG_FREE)
		return ;
	tmp = ft_var_address(msg, ptr);
	show_func(func, status, tmp);
	// if (tmp != NULL)
	//  	ft_free(tmp);
}

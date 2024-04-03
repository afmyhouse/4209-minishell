/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   999_debug_funcs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 23:29:02 by antoda-s          #+#    #+#             */
/*   Updated: 2024/04/04 00:39:52 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
int	show_func(const char *func_name, int status, char *msg_in)
{
	int					i;
	char				*msg;
	const t_debug_msg	debug_msg[14] = {
	{" INFO", SHOW_MSG, 5, "(ii) ", SBHPPL},
	{" START", FSTART, 6, "(>>) ", SHBLU},
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

	msg = ft_strdup(msg_in);

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

void	show_pointer(const char *func, int status, const char *msg, void *ptr)
{
	char	*ret;

	if (!DEBUG_FREE)
		return ;
	ret = ft_strjoin_free(ft_strjoin(msg, " -> "),
		ft_itoa_base((unsigned long)ptr, 'x'));
	show_func(func, status, ret);
	ft_free(ret);

}

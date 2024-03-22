/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   999_debug_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 23:29:02 by antoda-s          #+#    #+#             */
/*   Updated: 2024/03/22 19:41:02 by antoda-s         ###   ########.fr       */
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

char	*show_msg_setter(char *msg1, char *msg2)
{
	char	*msg;

	if (msg1 && msg2)
	msg = ft_strjoin_free(ft_strjoin_free(
					ft_strdup(msg1),
					ft_strdup(" -> ")),
				ft_strdup(msg2));
	else if (msg1)
		msg = ft_strdup(msg1);
	else if (msg2)
		msg = ft_strdup(msg2);
	else
		msg = ft_strdup("void message");
	return (msg);
}

void	show_msg_debug(char *fn, const t_debug_msg *debug_msg, int i, char *msg)
{
	if (!fn || !debug_msg || !msg)
		return ;
	if (DEBUG_COLOR)
	{
		printf("%s%s%s%s%s%s%s", SBHWHT, debug_msg[i].msg_header, SBWHT,
			fn, debug_msg[i].color, debug_msg[i].msg, SRST);
		if (msg)
			printf("%s-> %s%s\n", SBHCYN, msg, SRST);
		else
			printf("%s\n", SRST);
	}
	else
	{
		ft_putstr_fd(debug_msg[i].msg_header, STDERR_FILENO);
		ft_putstr_fd(fn, STDERR_FILENO);
		ft_putstr_fd(debug_msg[i].msg, STDERR_FILENO);
		show_func_msg(msg);
	}
}

/// @brief 				Shows the function name and status
/// @param func_name	Name of the function
/// @param status		Status of the function
/// @return				Status of the function
int	show_func(const char *func_name, int status, char *msg1, char *msg2)
{
	int					i;
	char				*msg;
	const t_debug_msg	debug_msg[10] = {{" INFO", INFO, 5, "(ii) ", SBHPPL},
	{" START", MY_START, 6, "(>>) ", SHBLU},
	{" ERROR", ERROR, 6, "(xx) ", SHRED},
	{" SUCCESS", SUCCESS, 8, "(xx) ", SHGRN},
	{" MALLOC", D_MALLOC, 7, "(**) ", SBHRED},
	{" FREE", D_FREE, 5, "(**) ", SBHRED},
	{" MALLOC_ERROR", MALLOC_ERROR, 13, "(xx) ", SBHRED},
	{" FILE_ERROR", FILE_ERROR, 11, "(xx) ", SBHRED},
	{" CHILD_EXIT", CHILD_EXIT, 11, "(xx) ", SBHYLW},
	{NULL, 0, 0, NULL, NULL}};

	if (!DEBUG_ALL || !DEBUG_FREE)
		return (-1);
	msg = show_msg_setter(msg1, msg2);
	i = -1;
	while (debug_msg[++i].status != status && debug_msg[i].msg)
		if (debug_msg[i].status == status)
			break ;
	show_msg_debug((char *)func_name, debug_msg, i, msg);
	ft_free(msg);
	return (status);
}

void	show_ptr(const char *func, int status, const char *varname, void *ptr)
{
	char	*tmp;

	if (!DEBUG_FREE)
		return ;
	tmp = ft_strjoin_free(ft_strjoin(varname, " -> "),
			ft_itoa_base((unsigned long)ptr, 'x'));
	show_func(func, status, tmp, NULL);
	ft_free(tmp);
}

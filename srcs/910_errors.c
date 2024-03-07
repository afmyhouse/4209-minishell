/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   910_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 22:37:00 by antoda-s          #+#    #+#             */
/*   Updated: 2024/03/02 01:13:53 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief 			Shows error and program sourcing it
/// @param msg		Message to show
/// @param system	Shows system error if true
/// @return			SUCCESS
int	export_error(const char *msg, int errms)
{
	// show_func(__func__, MY_START, NULL);

	char	*msgr;
	char	*msgt;
	int		status;

	msgt = ft_strjoin(msg, "': not a valid identifier");
	msgr = ft_strjoin("export: `", msgt);
	free(msgt);
	status = return_error(msgr, errms, 0);
	free(msgr);
	return (status);
}

/// @brief 			Shows error and program sourcing it
/// @param msg		Message to show
/// @param system	Shows system error if true
/// @return			SUCCESS
int	return_error(const char *msg, int errms, int errbash)
{
	// show_func(__func__, MY_START, NULL);
	if (!errbash)
		ft_putstr_fd("Minishell: ", 2);
	g_exit_status = errms;
	if (errbash)
	{
		g_exit_status = errno;
		perror(msg);
	}
	else
		ft_putendl_fd(msg, 2);
	//show_func(__func__, SUCCESS, NULL);
	return (1);
}
// void ft_strswap(char **s1, char **s2)
// {
// 	char	*tmp;

// 	if (!s1 || !s2)
// 		return ;
// 	tmp = *s1;
// 	*s1 = *s2;
// 	*s2 = tmp;
// }





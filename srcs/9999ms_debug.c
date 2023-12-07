/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 23:29:02 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/28 23:29:37 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/// @brief 				Shows the function name and status
/// @param func_name	Name of the function
/// @param status		Status of the function
/// @return				Status of the function
int	show_func(const char *func_name, int status)
{
	if (MY_DEBUG)
	{
		if (status == ERROR)
			printf("%s(X)%s %s : ERROR%s\n",SYLW, SRED, func_name, SWHT);
		else if (status == SUCCESS)
			printf("%s(X)%s %s : SUCCESS%s\n",SYLW, SGRN, func_name, SWHT);
		else if (status == MY_START)
			printf("%s(>)%s %s : START%s\n",SYLW, SYLW, func_name, SWHT);
	}
	return (status);
}
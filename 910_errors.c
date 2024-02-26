/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   910_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 22:37:00 by antoda-s          #+#    #+#             */
/*   Updated: 2024/02/13 19:42:38 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief 			Shows error and program sourcing it
/// @param msg		Message to show
/// @param system	Shows system error if true
/// @return			SUCCESS
int	export_error(const char *msg, int system)
{
	// show_func(__func__, MY_START, NULL);

	ft_putstr_fd("Minishell: export: '", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	errno = system;
	// show_func(__func__, SUCCESS, NULL);
	return (system);
}

/// @brief 			Shows error and program sourcing it
/// @param msg		Message to show
/// @param system	Shows system error if true
/// @return			SUCCESS
int	return_error(const char *msg, int errms, int errbash)
{
	// show_func(__func__, MY_START, NULL);
	ft_putstr_fd("Minishell: ", 2);
	g_exit_status = errms;
	if (errbash)
		perror(msg);
	else
		ft_putendl_fd(msg, 2);
	// show_func(__func__, SUCCESS, NULL);
	return (1);
}


/// @brief 		Alphatecially ordered array
/// @param src 	Array to order
/// @return 	Ordered array
char	**ordered_array(char **s, char t)
{
	char	**d;
	int		i, j, k, n;
	char	*swap;

	i = 0;
	while (s[i])
		i++;
	d = malloc(sizeof(char *) * (i + 1));
	if (!d)
		return (NULL);
	i = 0;
	while (s[i])
	{
		d[i] = s[i];
		i++;
	}
	d[i] = NULL;
	j = 0;
	n = 0;
	while (d[j] && d[j + 1])
	{
		i = j;
		while (d[j + 1])
		{
			j++;
			k = 0;
			printf("%sd[%d] = %s%s\n", SBHCYN, i, d[i], SRST);
			printf("%sd[%d] = %s%s\n", SBHCYN, j, d[j], SRST);
			while (d[i][k] != t && d[j][k] != t
				&& d[i][k] != '\0' && d[j][k] != '\0')
			{
				if ((d[i][k] > d[j][k]) || (d[i][k] != t && d[j][k] == t))
				{
					printf("%sd[%d][%d] = %c, d[%d][%d] = %c%s\n", SBHGRN, i, k, d[i][k], j, k, d[j][k], SRST);
					i = j;
					break ;
				}
				else if (d[i][k] < d[j][k] || (d[i][k] == t && d[j][k] != t))
				{
					printf("%sd[%d][%d] = %c, d[%d][%d] = %c%s\n", SBHRED, i, k, d[i][k], j, k, d[j][k], SRST);
					break ;
				}
				else
				{
					printf("%sd[%d][%d] = %c, d[%d][%d] = %c%s\n", SBHRED, i, k, d[i][k], j, k, d[j][k], SRST);
					k++;
				}
			}

		}
		swap = d[n];
		d[n] = d[i];
		d[i] = swap;
		printf("%sd[%d] = %s%s\n", SBHPPL, n, d[n], SRST);
		n++;
		j = n;
	}
	d[n] = NULL;
	//show_array(dst, "ordered");
	// show_func(__func__, SUCCESS, NULL);
	return (d);

}

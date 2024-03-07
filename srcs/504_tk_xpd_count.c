/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   504_tk_xpd_count.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 19:00:01 by antoda-s          #+#    #+#             */
/*   Updated: 2024/03/02 01:13:53 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @attention	>token builder< set of functions
/// @brief 		check is a '$' char is followed by valid valid identifier char
/// @param otk 	string sequence with a leading '$'
/// @param i 	index at '$' char
/// @return		addressed memory arg <i> is updated
void	tk_var_xpd_dolar_c(char *otk, int *i)
{
	// show_func(__func__, MY_START, NULL);
	(*i)++;
	if (otk[*i] && var_firstchar(otk[*i]) == SUCCESS)
		while (otk[*i] && var_name_checker(otk[*i]) == SUCCESS)
			(*i)++;
	else if (otk[*i] != '\"' && otk[*i] != '\'')
		(*i)++;
}

/// @attention	>token builder< set of functions
/// @brief 		looks for identifiers inside double quote string
///				if it find a '$' (var identifier init) it increments the
///				split index to point to next string sequence
/// @param otk	string sequence with a leading '\"'
/// @param spl 	split array indexer
/// @param i 	string sequence index
/// @return 	addressed memory <splits> and <i> updated
void	tk_var_xpd_dquote_c(char *otk, int *spl, int *i)
{
	int	xpd;
	// show_func(__func__, MY_START, NULL);

	xpd = 0;
	(*i)++;
	while (otk[*i] && otk[*i] != '\"')
	{
		if (otk[*i] == '$')
		{
			if (xpd == 0)
				(*spl)++;
			xpd = 1;
			tk_var_xpd_dolar_c(otk, i);
			(*spl)++;
		}
		else
		{
			(*i)++;
			xpd = 0;
		}
	}
	(*i)++;
}

/// @attention	>token builder< set of functions
/// @brief		leading '\'' char sequences are ignored and treated as plain
///				literals, without any kind of replacement or substitution.
///				The only purpose is to update <i> index	to the position	of the
///				char after trailing '\''
/// @param otk 	'\'' leading sequence to browse till its trailing '\''
/// @param i 	string sequence index
/// @return		addressed memory arg <i> is updated
void	tk_var_xpd_squote_c(char *otk, int *i)
{
	// show_func(__func__, MY_START, NULL);
	(*i)++;
	while (otk[*i] && otk[*i] != '\'')
		(*i)++;
	(*i)++;
}

/// @attention	>token builder< set of functions
/// @brief 		any char sequence else (that is not leaded by a splitter char:
///				'\"',  '\'',  '$'
/// @param otk 	sequence to browse till a splitter char is found
/// @param i 	string sequence index
/// @return		addressed memory arg <i> is updated
void	tk_var_xpd_else_c(char *otk, int *i)
{
	// show_func(__func__, MY_START, NULL);
	(*i)++;
	while (otk[*i] && otk[*i] != '$'
		&& otk[*i] != '\"' && otk[*i] != '\'')
		(*i)++;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 18:41:34 by antoda-s          #+#    #+#             */
/*   Updated: 2023/10/26 11:53:09 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/// @brief 		Adds the element ’new’ at the beginning of the list.
/// @param lst	The address of a pointer to the first link of a list.
/// @param	new	The address of a pointer to the element to be added to the list.
void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst && new)
	{
		(*new).next = *lst;
		*lst = new;
	}
}

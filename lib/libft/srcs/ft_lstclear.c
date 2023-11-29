/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 19:41:59 by antoda-s          #+#    #+#             */
/*   Updated: 2023/10/26 11:53:09 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/// @brief 		Deletes and frees the given element and every successor of
///				that element, using the function ’del’ and free(3).
/// @param lst	The address of a pointer to an element.
/// @param del	The address of the function used to delete the content of
///				the element.
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*lstclear;
	t_list	*lstnext;

	if (!lst)
		return ;
	lstclear = *lst;
	while (lstclear)
	{
		lstnext = (*lstclear).next;
		ft_lstdelone(lstclear, del);
		lstclear = lstnext;
	}
	*lst = NULL;
}

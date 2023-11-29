/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 21:34:39 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/03 13:08:52 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/// @brief 			Allocates memory for an array of nmemb elements of size
///					 bytes each and returns a pointer to the allocated memory.
/// @param item_qty	Number of elements
/// @param item_size	Size of each element
/// @return			Pointer to allocated memory
void	*ft_calloc(size_t item_qty, size_t item_size)
{
	void	*ptr;

	if (item_qty == 0 || item_size == 0)
	{
		item_qty = 1;
		item_size = 1;
	}
	ptr = (void *)malloc(item_qty * item_size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, item_qty * item_size);
	return ((void *)ptr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtheo <dtheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 08:27:16 by dtheo             #+#    #+#             */
/*   Updated: 2017/11/18 09:06:11 by dtheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(const void *content, size_t content_size)
{
	t_list	*elmt;

	if (!(elmt = (t_list *)ft_memalloc(sizeof(t_list))))
		return (NULL);
	if (content == NULL)
	{
		elmt->content = NULL;
		elmt->content_size = 0;
	}
	else
	{
		if (!(elmt->content = ft_memalloc(content_size)))
			return (NULL);
		ft_memcpy(elmt->content, content, content_size);
		elmt->content_size = content_size;
	}
	elmt->next = NULL;
	return (elmt);
}

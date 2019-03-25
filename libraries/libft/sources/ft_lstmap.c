/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtheo <dtheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 23:11:54 by dtheo             #+#    #+#             */
/*   Updated: 2017/11/18 08:59:21 by dtheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new_lst;
	t_list	*current;

	if (!(new_lst = (*f)(lst)))
		return (NULL);
	current = new_lst;
	while (lst->next)
	{
		lst = lst->next;
		if (!(current->next = (*f)(lst)))
			return (NULL);
		current = current->next;
	}
	return (new_lst);
}

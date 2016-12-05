/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinho <apinho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/13 01:57:56 by apinho            #+#    #+#             */
/*   Updated: 2016/09/20 15:33:42 by apinho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*tmp;
	t_list	*newlist;
	t_list	*tmp2;

	if (!lst)
		return (NULL);
	tmp2 = (*f)(lst);
	tmp = tmp2;
	newlist = tmp2;
	lst = lst->next;
	while (lst)
	{
		tmp2 = f(lst);
		if (tmp2 == NULL)
			return (NULL);
		tmp->next = tmp2;
		tmp = tmp2;
		lst = lst->next;
	}
	tmp2->next = NULL;
	return (newlist);
}

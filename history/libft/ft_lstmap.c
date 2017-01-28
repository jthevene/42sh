/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 17:34:26 by sgaudin           #+#    #+#             */
/*   Updated: 2016/02/03 10:24:02 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new_lst;
	t_list	*tmp;
	t_list	*stock;

	new_lst = NULL;
	if (!lst || !f)
		return (NULL);
	tmp = f(lst);
	if ((new_lst = ft_lstnew(tmp->content, tmp->content_size)))
	{
		stock = new_lst;
		lst = lst->next;
		while (lst)
		{
			tmp = f(lst);
			if (!(stock->next = ft_lstnew(tmp->content, tmp->content_size)))
				return (NULL);
			stock = stock->next;
			lst = lst->next;
		}
	}
	return (new_lst);
}

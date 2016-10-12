/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthevene <jthevene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/21 19:14:15 by jthevene          #+#    #+#             */
/*   Updated: 2015/01/06 22:36:00 by jthevene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list		*tmp;
	t_list		*dest;
	t_list		*res;

	tmp = lst;
	dest = 0;
	if (lst && f)
	{
		while (tmp)
		{
			res = f(tmp);
			ft_lstaddend(&dest, ft_lstnew(res->content, res->content_size));
			tmp = tmp->next;
		}
		return (dest);
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthevene <jthevene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/20 20:01:32 by jthevene          #+#    #+#             */
/*   Updated: 2015/01/04 18:50:26 by jthevene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*tmp1;
	t_list	*tmp2;

	if (alst && del)
	{
		tmp1 = *alst;
		while (tmp1)
		{
			del(tmp1->content, tmp1->content_size);
			tmp2 = tmp1->next;
			free(tmp1);
			tmp1 = tmp2;
		}
		*alst = NULL;
	}
}

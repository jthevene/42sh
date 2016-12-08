/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinho <apinho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/13 01:55:49 by apinho            #+#    #+#             */
/*   Updated: 2016/09/20 15:33:29 by apinho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*lst;
	t_list	*nextlist;

	if (!alst || !*alst)
		return ;
	lst = (*alst);
	nextlist = (*alst)->next;
	ft_lstdelone(&lst, del);
	if (nextlist)
		ft_lstdel(&nextlist, del);
	*alst = NULL;
}

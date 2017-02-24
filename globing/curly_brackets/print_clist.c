/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_clist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinho <apinho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 18:13:29 by apinho            #+#    #+#             */
/*   Updated: 2017/02/24 18:36:30 by apinho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/globing.h"

void				print_clist_list(t_clist **clist)
{
	rewind_tbracket(&(*clist)->list);
	while ((*clist)->list->next)
	{
		ft_putstr("Pattern : ");
		ft_putendl((*clist)->list->content);
		(*clist)->list = (*clist)->list->next;
	}
	ft_putstr("Pattern : ");
	ft_putendl((*clist)->list->content);
	ft_putchar('\n');
}

void				print_clist(t_clist **clist)
{
	rewind_tclist(&(*clist));
	while ((*clist)->next)
	{
		ft_putendl("/***** t_clist node : *****/\n");
		print_clist_list(&(*clist));
		(*clist) = (*clist)->next;
	}
	ft_putendl("/***** t_clist node : *****/\n");
	print_clist_list(&(*clist));
}

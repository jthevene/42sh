/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/10 11:16:13 by sgaudin           #+#    #+#             */
/*   Updated: 2016/02/03 10:25:47 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_print_list(t_list **alst)
{
	t_list	*tmp;

	tmp = *alst;
	if (alst != NULL && *alst != NULL)
	{
		if (ft_strlen((char*)tmp->content) < 20)
			tmp = tmp->next;
		while (tmp->next != NULL)
		{
			ft_putendl((char*)tmp->content);
			tmp = tmp->next;
		}
		ft_putendl((char*)tmp->content);
	}
}

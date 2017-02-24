/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinho <apinho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 18:13:29 by apinho            #+#    #+#             */
/*   Updated: 2017/02/24 18:33:58 by apinho           ###   ########.fr       */
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

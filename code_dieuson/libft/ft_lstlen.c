/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthevene <jthevene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/20 20:49:50 by jthevene          #+#    #+#             */
/*   Updated: 2014/11/22 16:49:27 by jthevene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_lstlen(t_list **alst)
{
	size_t		i;
	t_list		*tmp;

	i = 0;
	tmp = *alst;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

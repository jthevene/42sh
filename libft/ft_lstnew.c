/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthevene <jthevene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/19 19:13:03 by jthevene          #+#    #+#             */
/*   Updated: 2015/02/12 18:36:19 by jthevene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*newlm;

	if (content_size > 2147483648)
		return (NULL);
	newlm = malloc(sizeof(*newlm));
	if (newlm)
	{
		if (content)
		{
			newlm->content = ft_memalloc(content_size);
			ft_memcpy(newlm->content, content, content_size);
			newlm->content_size = content_size;
		}
		else
		{
			newlm->content = NULL;
			newlm->content_size = 0;
		}
		newlm->next = NULL;
	}
	return (newlm);
}

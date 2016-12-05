/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinho <apinho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/13 01:58:11 by apinho            #+#    #+#             */
/*   Updated: 2016/09/20 15:33:46 by apinho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*lst;
	void	*dst;

	if (!(dst = (void *)ft_memalloc(content_size)))
		return (NULL);
	if (content == NULL)
	{
		dst = NULL;
		content_size = 0;
	}
	else
		dst = ft_memcpy(dst, content, content_size);
	if (!(lst = (t_list*)ft_memalloc(sizeof(t_list))))
		return (NULL);
	lst->content = dst;
	lst->content_size = content_size;
	lst->next = NULL;
	return (lst);
}

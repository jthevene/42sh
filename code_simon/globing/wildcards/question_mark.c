/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   question_mark.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 12:26:45 by jules             #+#    #+#             */
/*   Updated: 2016/12/08 13:48:19 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/globing.h"

t_list 		*qmark_get_matching_content(t_list *dir_content, char *target)
{
	t_list	*matching_content;
	int 	len;

	matching_content = NULL;
	len = ft_strlen(target);
	while (dir_content && dir_content->content)
	{
		if (len = ft_strlen(dir_content->content))
		{
			matching_content = ft_lstnew(dir_content->content, len);
			matching_content = matching_content->next;
		}
		dir_content = dir_content->next;
	}
	return (matching_content);
}
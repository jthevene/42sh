/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   question_mark.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 12:26:45 by jules             #+#    #+#             */
/*   Updated: 2016/12/08 14:49:48 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/globing.h"

t_lst 		*qmark_get_matching_content(t_lst *dir_content, char *target)
{
	size_t 	len;
	t_lst	*matching;

	len = ft_strlen(target);
	matching = NULL;
	while (dir_content->next && dir_content->next->content)
	{
		if (len == ft_strlen(dir_content->content))
			ft_append_lst(&matching, ft_newlst(dir_content->content));
		dir_content = dir_content->next;
	}
	if (len == ft_strlen(dir_content->content))
		ft_append_lst(&matching, dir_content);
	ft_lst_rewind(&matching);
	ft_print_list_content(matching);
	return (matching);
}
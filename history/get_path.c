/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 14:00:47 by jules             #+#    #+#             */
/*   Updated: 2017/01/28 15:00:04 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/history.h"

t_lst		*get_dir_content(char *dir)
{
	t_lst				*dir_content;
	DIR 				*ret;
	struct dirent 		*direntt;

	dir_content = NULL;
	if (!(ret = opendir(dir)))
		return (NULL);
	while ((direntt = readdir(ret)))
		ft_append_lst(&dir_content, ft_newlst(direntt->d_name));
	return (dir_content);
}
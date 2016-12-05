/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 14:00:47 by jules             #+#    #+#             */
/*   Updated: 2016/12/05 16:28:41 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

t_list		*get_dir_content(char *dir)
{
	t_list				*dir_content;
	DIR 				*ret;
	struct dirent 		*direntt;
	char				*str;

	dir_content = NULL;
	str = NULL;
	if (!(ret = opendir(dir)))
		return (NULL);
	while ((direntt = readdir(ret)))
	{
		str = ft_strdup(ft_strpathjoin(dir, direntt->d_name));
		ft_lstaddend(&dir_content, ft_lstnew(str, ft_strlen(str)));
	}
	return (dir_content);
}

char	*ft_strpathjoin(const char *s1, const char *s2)
{
	int		i;
	int		j;
	char	*s3;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (!s1 || !s2)
		return ((s1) ? ft_strdup(s1) : ft_strdup(s2));
	j = ft_strlen(s1);
	if (s1[j - 1] == '/' || s2[0] == '/')
		return ((s1[j - 1] == '/' && s2[0] == '/') ? \
	ft_strjoin(s1, ++s2) : ft_strjoin(s1, s2));
		if (!(s3 = (char *)malloc((j + ft_strlen(s2) + 2))))
		return (NULL);
	i = 0;
	ft_strcpy(s3, s1);
	s3[j++] = '/';
	while (s2[i])
	{
		s3[j] = s2[i];
		j++;
		i++;
	}
	s3[j] = '\0';
	return (s3);
}

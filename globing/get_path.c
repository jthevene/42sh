/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 14:57:32 by sgaudin           #+#    #+#             */
/*   Updated: 2017/04/10 14:57:37 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/globing.h"

t_lst			*get_dir_content(char *dir)
{
	t_lst				*dir_content;
	DIR					*ret;
	struct dirent		*direntt;

	dir_content = NULL;
	if (!(ret = opendir(dir)))
		return (NULL);
	while ((direntt = readdir(ret)))
		ft_append_lst(&dir_content, ft_newlst(direntt->d_name));
	closedir(ret);
	return (dir_content);
}

char			*get_cmd_path(char *str)
{
	FT_INIT(int, i, 0);
	FT_INIT(char *, ret, NULL);
	FT_INIT(char *, tmp, NULL);
	while (str[i] && str[i] != '[' && str[i] != '*' && str[i] != '?')
		i++;
	while (i >= 0 && str[i] && str[i] != '/')
		i--;
	if (i < 0 || !str[i])
		return (NULL);
	else
	{
		tmp = ft_strsub(str, 0, i);
		ret = ft_strjoin(tmp, "/");
		free(tmp);
		return (ret);
	}
}

char			*get_cmd_last_path(char *str)
{
	FT_INIT(int, i, 0);
	FT_INIT(int, j, 0);
	FT_INIT(char *, ret, NULL);
	while (str[i] && str[i] != '[' && str[i] != '*' && str[i] != '?')
		i++;
	while (str[i] && str[i] != '/')
		i++;
	if (!str[i])
		return (NULL);
	else
	{
		j = i;
		while (str[j])
			j++;
		ret = ft_strsub(str, i, j - i);
		return (ret);
	}
}

char			*ft_strpathjoin(const char *s1, const char *s2)
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

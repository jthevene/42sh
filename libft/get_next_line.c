/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthevene <jthevene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/23 19:19:09 by jthevene          #+#    #+#             */
/*   Updated: 2015/11/16 17:27:16 by jthevene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_newline(char *str)
{
	char		*tmp;

	if (str)
	{
		tmp = str;
		while (*tmp)
		{
			if (*tmp == '\n')
				return (tmp - str);
			tmp++;
		}
	}
	return (-1);
}

static void		ft_straddend(char **str, char *buf, size_t len)
{
	char		*tmp;

	buf[len] = '\0';
	if (!*str)
		tmp = ft_strdup(buf);
	else
		tmp = ft_strjoin(*str, buf);
	free(*str);
	*str = tmp;
}

static int		ft_splitline(char **str, char **line, int endl)
{
	char		*tmp;
	int			len;

	if (!*str || !**str)
		return (0);
	tmp = 0;
	if (endl < 0)
		*line = ft_strdup(*str);
	else
	{
		*line = ft_strsub(*str, 0, endl);
		len = ft_strlen(*str + endl);
		if (len)
			tmp = ft_strsub(*str, endl + 1, len - 1);
	}
	free(*str);
	*str = tmp;
	return (1);
}

int				get_next_line(int const fd, char **line)
{
	char			*buf;
	ssize_t			ret;
	static char		*str;
	int				endl;

	ret = 1;
	if (BUFF_SIZE > 830000)
		return (-1);
	buf = malloc(sizeof(char *) * (BUFF_SIZE + 1));
	if (!str)
		str = 0;
	if (!line)
		return (-1);
	while ((endl = ft_newline(str)) < 0 && ret)
	{
		if ((ret = read(fd, buf, BUFF_SIZE)) == -1)
			return (-1);
		if (ret > 0)
			ft_straddend(&str, buf, ret);
	}
	return (ft_splitline(&str, line, endl));
}

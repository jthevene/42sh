/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjacque <hjacque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 18:13:29 by hjacque           #+#    #+#             */
/*   Updated: 2017/03/08 14:51:29 by hjacque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/get_next_line.h"

static void		join_rest(char **rest, char *buf)
{
	char *tmp;

	tmp = ft_strnew(ft_strlen(*rest) + ft_strlen(buf));
	ft_strcat(tmp, *rest);
	ft_strcat(tmp, buf);
	ft_memdel((void**)&*rest);
	*rest = ft_strnew(ft_strlen(tmp));
	ft_strcpy(*rest, tmp);
	ft_memdel((void**)&tmp);
}

static int		write_line(char **rest, char *end, char **line)
{
	char	*sub;

	if (end == NULL)
	{
		ft_memdel((void**)&*line);
		*line = ft_strdup(*rest);
		return (1);
	}
	sub = ft_strsub(*rest, 0, (ft_strlen(*rest) - ft_strlen(end) - 1));
	ft_memdel((void**)&*line);
	if (!(*line = ft_strnew(ft_strlen(sub))))
		return (-1);
	ft_strcpy(*line, sub);
	ft_memdel((void**)&sub);
	ft_memdel((void**)&*rest);
	*rest = ft_strnew(ft_strlen(end));
	ft_strcpy(*rest, end);
	return (1);
}

static int		end_line(char **rest, char **line, int const fd, char *buf)
{
	int		ret_read;
	char	*end;
	char	*tmp;

	while (1)
	{
		if (ft_strchr(*rest, '\n') != NULL)
		{
			tmp = ft_strdup(*rest);
			end = ft_strchr(tmp, '\n');
			end = end + 1;
			write_line(rest, end, line);
			ft_memdel((void**)&tmp);
			return (1);
		}
		ft_bzero(buf, BUFF_SIZE);
		if ((ret_read = read(fd, buf, BUFF_SIZE)) == 0)
		{
			if (ft_strlen(*rest) > 0)
				write_line(rest, NULL, line);
			return (0);
		}
		join_rest(rest, buf);
	}
}

static	int		init_char(char **line, char **buf)
{
	if (!(*line = ft_strnew(1)))
		return (0);
	if (!(*buf = ft_strnew(BUFF_SIZE)))
		return (0);
	return (1);
}

int				get_next_line(int const fd, char **line)
{
	static char		*rest[256] = {NULL};
	int				ret;
	char			*buf;
	char			*tmp;

	if (fd < 0 || fd == 1 || fd == 2 || BUFF_SIZE <= 0 || !line)
		return (-1);
	if (!rest[fd % 256])
	{
		if (!(rest[fd % 256] = ft_strnew(BUFF_SIZE)))
			return (-1);
		if (read(fd, rest[fd % 256], BUFF_SIZE) == -1)
			return (-1);
	}
	if (!init_char(line, &buf))
		return (-1);
	tmp = buf;
	ret = end_line(&rest[fd % 256], line, fd, buf);
	ft_memdel((void **)&tmp);
	if (ret == 0 && ft_strlen(rest[fd % 256]) > 0)
	{
		ft_memdel((void**)&rest[fd % 256]);
		return (1);
	}
	return (ret);
}

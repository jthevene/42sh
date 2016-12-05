/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinho <apinho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/21 16:44:56 by apinho            #+#    #+#             */
/*   Updated: 2016/09/26 14:11:40 by apinho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"
#include "../libft/libft.h"

static int		ft_get_last_line(char **line, char **stck, t_var *v)
{
	int		len;

	len = ft_strlen(v->tmp);
	if (v->i == 0 && len > 0)
	{
		*line = ft_strncpy(ft_strnew(len), v->tmp, len);
		free(v->tmp);
		free(v->buf);
		ft_bzero(*stck, BUFF_SIZE);
		v->i = 1;
	}
	else
		*line = NULL;
	return (v->i);
}

int				get_next_line(int const fd, char **line)
{
	static char	*stck;
	t_var		v;

	if (BUFF_SIZE < 1 || !line)
		return (-1);
	stck = (stck == NULL) ? ft_strnew(BUFF_SIZE) : stck;
	if (!(v.buf = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1))) \
		|| !(v.tmp = ft_strncpy(ft_strnew(BUFF_SIZE), stck, BUFF_SIZE)))
		return (-1);
	while (ft_strchr(v.tmp, '\n') == 0)
	{
		if ((v.i = read(fd, v.buf, BUFF_SIZE)) < 1)
			return (ft_get_last_line(line, &stck, &v));
		v.buf[v.i] = '\0';
		v.tmp = ft_strjoinfree(v.tmp, v.buf, 1);
	}
	free(v.buf);
	v.i = (size_t)(ft_strchr(v.tmp, '\n') - v.tmp);
	*line = ft_strncpy(ft_strnew(v.i), v.tmp, v.i);
	ft_bzero(stck, BUFF_SIZE);
	stck = ft_strncpy(stck, ft_strchr(v.tmp, '\n') + 1, BUFF_SIZE);
	free(v.tmp);
	return (1);
}

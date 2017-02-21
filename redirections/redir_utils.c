/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/30 14:52:21 by sgaudin           #+#    #+#             */
/*   Updated: 2017/02/21 13:17:52 by jthevene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

char		*get_filename(char *line, int i)
{
	FT_INIT(char *, filename, NULL);
	FT_INIT(int, j, i);
	while (line[j] && line[j] != ' ')
		j++;
	if (!(filename = ft_strsub(line, i, j - i)))
		return (NULL);
	return (filename);
}

int			get_fd_in(char *line, int i)
{
	FT_INIT(int, j, i);
	FT_INIT(char *, fd_in_char, NULL);
	FT_INIT(int, fd_in, 0);
	if (!line[j - 1] || !ft_isdigit(line[j - 1]))
		return (1);
	j--;
	while (line[j] && ft_isdigit(line[j]))
		j--;
	if (!(fd_in_char = ft_strsub(line, j + 1, i - j)))
		return (1);
	fd_in = ft_atoi(fd_in_char);
	ft_strdel(&fd_in_char);
	return (fd_in);
}

t_fdlist	*new_node_fdlist(char *filename, int fd_in, int type)
{
	FT_INIT(t_fdlist, *new, NULL);
	if (!(new = (t_fdlist *)malloc(sizeof(t_fdlist))))
		return (NULL);
	new->prev = NULL;
	new->next = NULL;
	new->type = type;
	new->fd_in = fd_in;
	if (type == SIMPLE)
		new->fd_file = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == DOUBLE)
		new->fd_file = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		new->fd_file = type;
	if (new->fd_file == -1)
	{
		free(new);
		return (NULL);
	}
	new->filename = ft_strdup(filename);
	return (new);
}

void		free_fdlist(t_fdlist **fdlist, int go_close)
{
	FT_INIT(t_fdlist, *tmp, NULL);
	if (!fdlist || !(*fdlist))
		return ;
	while ((*fdlist)->prev)
		(*fdlist) = (*fdlist)->prev;
	while ((*fdlist)->next)
	{
		if ((*fdlist)->filename)
			ft_strdel(&(*fdlist)->filename);
		if (go_close == 1)
			close((*fdlist)->fd_file);
		tmp = (*fdlist);
		(*fdlist) = (*fdlist)->next;
		free(tmp);
	}
	if ((*fdlist)->filename)
		ft_strdel(&(*fdlist)->filename);
	if (go_close == 1)
		close((*fdlist)->fd_file);
	free((*fdlist));
	(*fdlist) = NULL;
}

char		*delete_right_redirs_str(char *str)
{
	FT_INIT(int, i, 0);
	FT_INIT(int, j, 0);
	FT_INIT(char *, tmp, NULL);
	FT_INIT(char *, tmp2, NULL);
	while (str[i] && i < (int)ft_strlen(str))
	{
		if (str[i] == '>')
		{
			while (str[i] && str[i] != ' ')
				i--;
			j = i;
			while (str[j] && str[j - 1] != '>')
				j++;
			if (str[j] == '>')
				j++;
			while (str[j] && str[j] == ' ')
				j++;
			while (str[j] && str[j] != ' ')
				j++;
			tmp2 = ft_strsub(str, i, j - i);
			tmp = ft_str_replace(str, tmp2, "");
			ft_strdel(&tmp2);
			ft_strdel(&str);
			str = ft_strdup(tmp);
			ft_strdel(&tmp);
		}
		i++;
	}
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edition.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 11:01:23 by jules             #+#    #+#             */
/*   Updated: 2016/11/03 11:59:15 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void 	add_char(char c)
{
	FT_INIT(int, pos_x, g_shell.cursor_x - 3);
	FT_INIT(int, i, 0);
	FT_INIT(int, len, ft_strlen(g_shell.current_line));
	FT_INIT(char*, second_part, ft_strsub(g_shell.current_line, pos_x, (len - pos_x)));
	g_shell.current_line[pos_x] = c;
	pos_x++;
	while (second_part && second_part[i])
	{
		g_shell.current_line[pos_x] = second_part[i];
		pos_x++;
		i++;
	}
	ft_strdel(&second_part);
	g_shell.current_line[pos_x] = '\0';
}

void 	fill_btwn_char(char c)
{
	FT_INIT(int, len, ft_strlen(g_shell.current_line));
	FT_INIT(char*, tmp, NULL);
	if (len % 256 == 255)
	{
		tmp = g_shell.current_line;
		g_shell.current_line = (char*)malloc(sizeof(char) * (len + 1 + 256));
		ft_strcpy(g_shell.current_line, tmp);
		ft_strdel(&tmp);
	}
	add_char(c);
}

void	fill_current_line(char c)
{
	char	*tmp;
	int 	len;

	tmp = NULL;
	len = 0;
	if (!g_shell.current_line)
		g_shell.current_line = (char*)malloc(sizeof(char) * 256);
	else
	{
		len = ft_strlen(g_shell.current_line);
		if (g_shell.cursor_x < (len + 3))
			return (fill_btwn_char(c));
		if (len % 256 == 255)
		{
			tmp = g_shell.current_line;
			g_shell.current_line = (char*)malloc(sizeof(char) * (len + 1 + 256));
			ft_strcpy(g_shell.current_line, tmp);
			free(tmp);
		}
	}
	g_shell.current_line[len] = c;
	g_shell.current_line[len + 1] = '\0';
}

// ajoute le caractere c à la fin de current_line

/*void	fill_current_line(char c)
{
	char	*tmp;
	int 	len;

	tmp = NULL;
	len = 0;
	if (!g_shell.current_line)
		g_shell.current_line = (char*)malloc(sizeof(char) * 256);
	else
	{
		len = ft_strlen(g_shell.current_line);
		if (len % 256 == 255)
		{
			tmp = g_shell.current_line;
			g_shell.current_line = (char*)malloc(sizeof(char) * (len + 1 + 256));
			ft_strcpy(g_shell.current_line, tmp);
			free(tmp);
		}
	}
	g_shell.current_line[len] = c;
	g_shell.current_line[len + 1] = '\0';
}*/
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edition.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjacque <hjacque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:36:42 by hjacque           #+#    #+#             */
/*   Updated: 2017/03/08 14:45:43 by hjacque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh42.h"

void			add_char(char c)
{
	FT_INIT(int, pos_x, g_shell.cursor_x - g_shell.prompt_len);
	FT_INIT(int, i, 0);
	FT_INIT(int, len, ft_strlen(g_shell.current_line));
	FT_INIT(char*, second_part, ft_strsub(g_shell.current_line, pos_x,
		(len - pos_x)));
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

void			backspace_key(int key)
{
	FT_INIT(int, len, ft_strlen(g_shell.current_line));
	FT_INIT(int, cursor_pos, g_shell.cursor_x - (g_shell.prompt_len + 1));
	if (!len || !g_shell.current_line || (cursor_pos < 0 && key == K_BACKSP))
	{
		g_shell.cursor_x = g_shell.prompt_len;
		return ;
	}
	if (key == K_BACKSP)
		g_shell.cursor_x--;
	else if (key == K_DEL)
		cursor_pos++;
	while (cursor_pos < len)
	{
		g_shell.current_line[cursor_pos] = g_shell.current_line[cursor_pos + 1];
		cursor_pos++;
	}
	g_shell.current_line[cursor_pos] = '\0';
	if (key)
		print_line(-1);
}

void			fill_btwn_char(char c)
{
	FT_INIT(int, len, ft_strlen(g_shell.current_line));
	FT_INIT(char*, tmp, NULL);
	if (len % 256 == 255)
	{
		tmp = g_shell.current_line;
		g_shell.current_line = ft_strnew(len + 1 + 256);
		ft_strcpy(g_shell.current_line, tmp);
		ft_strdel(&tmp);
	}
	add_char(c);
}

void			fill_current_line(char c)
{
	char	*tmp;
	int		len;

	tmp = NULL;
	len = 0;
	if (!g_shell.current_line)
		g_shell.current_line = (char*)malloc(sizeof(char) * 256);
	else
	{
		len = ft_strlen(g_shell.current_line);
		if (g_shell.cursor_x < (len + g_shell.prompt_len))
			return (fill_btwn_char(c));
		if (len % 256 == 255)
		{
			tmp = g_shell.current_line;
			g_shell.current_line = ft_strnew(len + 1 + 256);
			ft_strcpy(g_shell.current_line, tmp);
			ft_strdel(&tmp);
		}
	}
	g_shell.current_line[len] = c;
	g_shell.current_line[len + 1] = '\0';
}

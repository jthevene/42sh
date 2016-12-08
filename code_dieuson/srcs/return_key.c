/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 13:12:22 by jules             #+#    #+#             */
/*   Updated: 2016/12/08 13:51:17 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <42sh.h>

static void 	set_cursor_pos_to_end(int i)
{
	FT_INIT(int, dif_x, g_shell.line_size - g_shell.cursor_x);
	if (i)
		i--;
	while (dif_x > 0)
	{
	 	arrow_moove_right();
		dif_x--;
	}
	if (g_shell.cursor_2d_x)
		ft_putstr("\n");
}


void	return_key(void)
{ 
	if (ft_strlen(g_shell.current_line))
	{
		ft_putchar(10);
		g_shell.line = ft_strdup(g_shell.current_line);
		glob_parser();
		free(g_shell.line);
		set_cursor_pos_to_end(g_shell.line_size);
		if (g_shell.hist->content)
			ft_newhist(g_shell.current_line);
		else
			g_shell.hist->content = ft_strdup(g_shell.current_line);
			g_shell.hist->number++;
		g_shell.current_line = NULL;
		g_shell.nav_hist = 0;
		ft_bzero(g_shell.current_line, ft_strlen(g_shell.current_line));
	}
	else
		ft_putchar(10);
	display_prompt();
}

void	backspace_key(int key)
{
	FT_INIT(int, len, ft_strlen(g_shell.current_line));
	FT_INIT(int, cursor_pos, g_shell.cursor_x - 4);
	if (!len || !g_shell.current_line || (cursor_pos < 0 && key == K_BACKSP))
	{
		g_shell.cursor_x = 3;
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

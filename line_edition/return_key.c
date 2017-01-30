/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 13:12:22 by jules             #+#    #+#             */
/*   Updated: 2017/01/28 14:43:40 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/42sh.h"

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
/*
void	detect_builtins(void)
{
	if (ft_strstr(g_shell.line, "echo"))
		_42sh_echo(g_shell.line);
	else if (ft_strstr(g_shell.line, "unsetenv"))
		_42sh_unsetenv(g_shell.line);
	else if (ft_strstr(g_shell.line, "setenv"))
		_42sh_setenv(g_shell.line);
	else if (ft_strstr(g_shell.line, "env"))
		_42sh_env();
}*/

void	return_key(void)
{ 
	go_to_end();
	if (ft_strlen(g_shell.current_line))
	{
		lexer_parser(g_shell.current_line);
		ft_putchar(10);
		g_shell.line = ft_strdup(g_shell.current_line);
		glob_parser();
		distrib_functions();
//		detect_builtins();
//		cd(g_shell.line);
		free(g_shell.line);
		set_cursor_pos_to_end(g_shell.line_size);
		if (g_shell.current_line && !g_shell.hist_opt.p) //on ajoute la ligne à l'historique seulement si la ligne est non nulle && si pas history -p
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
	g_shell.curr_hist = g_shell.hist;
	g_shell.len = 0;
	display_prompt();
}

void	backspace_key(int key)
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

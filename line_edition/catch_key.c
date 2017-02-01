/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvirgile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 17:16:00 by dvirgile          #+#    #+#             */
/*   Updated: 2017/01/16 17:16:00 by dvirgile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/42sh.h"

int 			detect_selection_text(char *key, int start ,
												 int end , int cursor_x)
{
	if (key[4] == 50 && key[5] == 67) 	// Selection zone de text SHIFT + RIGHT
	{
		g_shell.start_select = start ? start : cursor_x;
		g_shell.end_select = (end && end == cursor_x ?
			cursor_x + 1 : cursor_x);
		if (g_shell.end_select >= g_shell.line_size)
			g_shell.end_select = g_shell.line_size - 1;
		print_line(g_shell.line_size);
		return (K_RIGHT);
	}
	else if (key[4] == 50 && key[5] == 68) // Selection zone de text SHIFT + LEFT
	{
		g_shell.start_select = start ? start : cursor_x - 1;
		if (end && end < cursor_x)
			g_shell.end_select = cursor_x;
			if (end && end < cursor_x && cursor_x == start + 1)
				g_shell.end_select = g_shell.end_select > g_shell.prompt_len ?
					g_shell.end_select - 1 : g_shell.end_select;
			else if (end && end < cursor_x)
				g_shell.end_select = g_shell.end_select > g_shell.prompt_len ?
					g_shell.end_select - 2 : g_shell.end_select;
		if (!(end && end < cursor_x))
			g_shell.end_select = cursor_x > g_shell.prompt_len ? cursor_x - 1 : cursor_x;
		print_line(g_shell.line_size);
		return (K_LEFT);
	}
	return (0);
}

int 			arrow_combo(char *key)
{
	if (key[2] != 49 || key[3] != 59)
		return (0);
	if (key[4] == 53 && key[5] == 67)
		return (K_OW_RIGHT); // OW -> ONE WORD
	else if (key[4] == 53 && key[5] == 68)
		return (K_OW_LEFT);
	else if (key[4] == 53 && key[5] == 65)
		return (K_OL_UP); 	// OL -> ONE LINE
	else if (key[4] == 53 && key[5] == 66)
		return (K_OL_DOWN);
	else
		return (detect_selection_text(key, g_shell.start_select,
			g_shell.end_select, g_shell.cursor_x));
}

int 			detect_arrow(char *key)
{
	if (!(key[4] == 50 && (key[5] == 67 || key[5] == 68 ||
		key[5] == 65 || key[5] == 66)))
	{
		MULTI(g_shell.start_select, g_shell.end_select, 0); // On remet a zero la zone de selection
		print_line(g_shell.line_size);
	}
	if (key[0] != 27 || key[1] != 91)
		return (0);
	if (key[2] == 67 && key[3] == 0)
		return (K_RIGHT);
	else if (key[2] == 68 && key[3] == 0)
		return (K_LEFT);
	else if (key[2] == 65 && key[3] == 0)
		return (K_UP);
	else if (key[2] == 66 && key[3] == 0)
		return (K_DOWN);
	return (arrow_combo(key));
}

int 		is_arrow(char *key)
{
	if (key[0] == 27 && key[1] == 91 && key[2] == 49
		&& key[3] == 59 && key[4] == 53)
		return (1);
	if ((key[0] == 27 && key[1] == 91 && (key[2] != 51
		&& key[2] != 70 && key[2] != 72)))
		return (1);
	return (0);
}

 int		readkeyspecial(char *key)
{
//	readkeyspecial2();
	if (key[0] == 27 && key[1] == 99) // ALT + C
	{
//		ft_putendl("COPY");
		return (K_COPY);
	}
	else if (key[0] == 27 && key[1] == 0) // ECHAP
	{
//		ft_putendl("ECHAP");
		return (K_ESCAPE);
	}
	else if (key[0] == 27 && key[1] == 118) // ALT + V
		return (K_PAST);
	else if (is_arrow(key))
		return (detect_arrow(key));
	else if (key[0] == 27 && key[1] == 91 && key[2] == 51 && key[3] == 126)
		return (K_DEL);
	else if (key[0] == 27 && key[1] == 91 && key[2] == 72)
		return (K_GO_START);
	else if (key[0] == 27 && key[1] == 91 && key[2] == 70)
		return (K_GO_END);
	return (K_UNKNOWN);
}

int				readkey(void)
{
	FT_INIT(char*, c, g_shell.c);
	ft_bzero(c, 16);
	if (read(STDIN_FILENO, c, 15))// on bloque ici en attendant au moins 1 byte
	{
		FT_INIT(int, i, 0);
		while (c[i] != 0)
		{
//			printf("c =%d,\n", c[i]);
			i++;
		}
		if (c[0] == 27)// caractere d'echappement recu
			return (readkeyspecial(c));// on doit donc traiter une touche speciale codee sur plusieurs bytes
	}
	if (c[0] == 4 && c[1] == 0) // CTRL + D
		return (K_ESCAPE);
	else if (c[0] > 31 && c[0] < 127)
		return (K_PRINT);
	else if (c[0] == 5) // CTRL + E
		return (K_COPY);
	else if (c[0] == 9) // TAB
		return (K_TAB);
	else if (c[0] == 18) // CTRL + R
		return (K_CUT);
	else if (c[0] == 20) // PAST CTRL + T
		past_line(g_shell.clipboard);
	else if (c[0] == 127)
		return (K_BACKSP);
	else if (c[0] == 10)
		return (K_RETURN);
	return (K_UNKNOWN);
}

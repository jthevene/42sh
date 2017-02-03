#include "../includes/sh.h"

static void 	modif_prompt(char *modif_by)
{
	if (g_shell.prompt)
		ft_strdel(&g_shell.prompt);
	g_shell.prompt = ft_strdup(modif_by);
	g_shell.prompt_len = ft_strlen(g_shell.prompt);	
}

static int 		detect_input_type(int key, char *quote_type)
{
	if (key == K_DEL)
		backspace_key(K_DEL);
	else if (key == K_BACKSP)
		backspace_key(K_BACKSP);
	else if (key == K_RIGHT || key == K_LEFT)
		distrib_cursor_moves(key);
	else if (key == K_UP || key == K_DOWN)
	{
		distrib_cursor_moves(key);
		modif_prompt(quote_type);
	}
	else if (key == K_PRINT)
		return (1);
	return (0);
}


char			*prompt_dquote(char *quote_type)
{
	FT_INIT(int, key, 0);
	g_shell.cursor_x = ft_strlen(quote_type);
	tputs(tgetstr("sc", NULL), 1, ft_putchar_int);
	modif_prompt(quote_type);
	ft_bzero(g_shell.c, 16);
	ft_bzero(g_shell.current_line, ft_strlen(g_shell.current_line));
	print_line(1);
	while ((key = readkey()))
	{
		if (g_shell.c[0] == 10)
			break ;
		else if (detect_input_type(key, quote_type) == K_PRINT)
		{
			fill_current_line(g_shell.c[0]);
			g_shell.cursor_x++;
		}
		print_line(1);
	}
	return (g_shell.current_line);
}
#include "42sh.h"

static char 	*store_selection(int start_select, int end_select, int key)
{
	FT_INIT(char*, clipboard, NULL);
	FT_INIT(int, nb_del, 0);
	clipboard = ft_strsub(g_shell.current_line, start_select,
		end_select - start_select);
	if (key == K_CUT)
	{
		nb_del = end_select - start_select;
		end_select = nb_del;
		while (g_shell.cursor_x > g_shell.start_select && nb_del--)
			arrow_moove_left();
		nb_del = end_select;
		g_shell.cursor_x++;
		while (nb_del--)
			backspace_key(0);
		g_shell.cursor_x--;
	}
	MULTI(g_shell.start_select, g_shell.end_select, 0);
	print_line(g_shell.line_size);
	if (g_shell.clipboard)
		ft_strdel(&g_shell.clipboard);
	return (clipboard);
}

void 	copy_cut_line(int key)
{
	FT_INIT(int, start_select, -3);
	FT_INIT(int, end_select, -3);
	if (!g_shell.start_select || !g_shell.end_select)
	{
		ft_putstr("Error Copy/Cut no selection");
		return ;
	}
	start_select += g_shell.start_select < g_shell.end_select ?
		g_shell.start_select : g_shell.end_select;
	end_select += g_shell.end_select > g_shell.start_select ?
		g_shell.end_select : g_shell.start_select;
	end_select++;
	if (end_select - start_select <= 0)
	{
		ft_putstr("Error selections <= 0\n");
		return ;
	}
	g_shell.clipboard = store_selection(start_select, end_select, key);
}

void 	past_line(char *clipboard)
{
	FT_INIT(int, i, 0);
	if (!clipboard)
	{
		ft_putstr("ERROR: No clipboard\n");
		return ;
	}
	while (clipboard[i])
	{
		fill_current_line(clipboard[i]);
		g_shell.cursor_x++;
		i++;
	}
	print_line(g_shell.line_size);
}
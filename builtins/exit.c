#include "../includes/42sh.h"

void ft_exit(void)
{
	go_to_end();
	ft_putstr("\n");
	ft_reset_termios(g_shell.t_back);
	update_history_file(NULL, get_histsize("HISTFILESIZE"));
	exit(0);
}
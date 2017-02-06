#include "../includes/sh.h"

int		error_parse(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	if (check_type_ope(tmp->type))
	{
		leave_error();
		return (0);
	}
	while(tmp->next)
	{
		if (check_type_ope(tmp->type) && check_type_ope(tmp->next->type))
		{
			leave_error();
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int		check_type_ope(int type)
{
	if (type == OR || type == AND || type == PIPE \
		|| type == DLESS || type ==  DMORE || type == LESS \
		|| type == MORE || type == SEMICOLON)
		return (1);
	return (0);
}

void	leave_error(void)
{
	ft_putstr("Syntax Error");
	go_to_end();
 	if (g_shell.current_line)
		ft_bzero(g_shell.current_line, g_shell.line_size - 
				g_shell.prompt_len);
}

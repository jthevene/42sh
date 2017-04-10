/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinho <apinho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:36:40 by hjacque           #+#    #+#             */
/*   Updated: 2017/04/10 12:13:45 by apinho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

int		error_parse(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	if (check_type_ope(tmp->type))
		return (leave_error());
	while (tmp->next)
	{
		if (check_type_ope(tmp->type) && check_type_ope(tmp->next->type))
			return (leave_error());
		else if (tmp->type == 50)
			return (leave_error());
		tmp = tmp->next;
	}
	if (tmp->type == DLESS || tmp->type == DMORE || tmp->type == LESS \
		|| tmp->type == MORE || tmp->type == 50)
		return (leave_error());
	return (1);
}

int		check_type_ope(int type)
{
	if (type == OR || type == AND || type == PIPE
		|| type == DLESS || type == DMORE || type == LESS
		|| type == MORE || type == SEMICOLON)
		return (1);
	return (0);
}

int		leave_error(void)
{
	ft_putstr("Syntax Error\n");
	go_to_end();
	if (g_shell.current_line)
		ft_bzero(g_shell.current_line, g_shell.line_size -
				g_shell.prompt_len);
	return (0);
}

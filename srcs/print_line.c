/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 10:41:51 by jules             #+#    #+#             */
/*   Updated: 2016/10/18 15:22:48 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void	clean_line(int i)
{
	i += 3;
	tputs(tgetstr("dl", NULL), 1, ft_putchar_int);
	// tputs(tgoto("ch", 0, 0), 1, ft_putchar_int);
	while (i-- > 0)
		tputs(tgetstr("le", NULL), 1, ft_putchar_int);
}

void	print_line(int i)
{
	clean_line(i);
	display_prompt();
	ft_putstr(g_shell.current_line);	
}
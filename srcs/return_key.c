/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 13:12:22 by jules             #+#    #+#             */
/*   Updated: 2016/10/18 16:09:42 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <42sh.h>

void	return_key(void)
{ 

	// INSEREZ VOS FONCTIONS AU DESSUS
	if (g_shell.current_line)
	{
		ft_newhist(g_shell.current_line);
		g_shell.current_line = NULL;
	}
	cursor_next_line();
	display_prompt();
}

void	backspace_key(void)
{
	char	*tmp;
	int 	len;

	if (g_shell.current_line)
	{
		if ((len = ft_strlen(g_shell.current_line)) > 0)
		{
			tmp = ft_strdup(g_shell.current_line);
			if (!(g_shell.current_line = (char*)malloc(sizeof(char) * len)))
				return;
			g_shell.current_line = ft_strncpy(g_shell.current_line, tmp, len - 1);
			ft_cursor_left(1);
			print_line(len - 1);
		}
	}
}

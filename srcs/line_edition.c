/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edition.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 11:01:23 by jules             #+#    #+#             */
/*   Updated: 2016/11/03 11:59:15 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

// ajoute le caractere c à la fin de current_line
void	fill_current_line(char c)
{
	char	*tmp;
	int 	len;

	tmp = NULL;
	len = 0;
	if (!g_shell.current_line)
		g_shell.current_line = (char*)malloc(sizeof(char) * 256);
	else
	{
		len = ft_strlen(g_shell.current_line);
		if (len % 256 == 255)
		{
			tmp = g_shell.current_line;
			g_shell.current_line = (char*)malloc(sizeof(char) * (len + 1 + 256));
			ft_strcpy(g_shell.current_line, tmp);
			free(tmp);
		}
	}
	g_shell.current_line[len] = c;
	g_shell.current_line[len + 1] = '\0';
}
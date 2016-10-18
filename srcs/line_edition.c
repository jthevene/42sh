/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edition.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 11:01:23 by jules             #+#    #+#             */
/*   Updated: 2016/10/18 10:59:01 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void	fill_current_line(char c)
{
	char	tmp1[2];
	char	*tmp2;
	int 	len;

	tmp2 = NULL;
	len = 0;
	if (!g_shell.current_line)
	{
		if (!(g_shell.current_line = (char*)malloc(sizeof(char) * 2)))
			return;
		g_shell.current_line[0] = c;
		g_shell.current_line[1] = '\0';		
	}
	else
	{
		tmp1[0] = c;
		tmp1[1] = '\0';
		tmp2 = ft_strdup(g_shell.current_line);
		len = ft_strlen(g_shell.current_line);
		if (!(g_shell.current_line = (char*)malloc(sizeof(char) * len + 2)))
			return;
		g_shell.current_line = ft_strcat(tmp2, tmp1);
		free(tmp2);
	}
}
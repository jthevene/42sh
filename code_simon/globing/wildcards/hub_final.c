/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hub_final.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 09:37:08 by sgaudin           #+#    #+#             */
/*   Updated: 2016/12/07 09:37:09 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/globing.h"

void		g_parse_expr(char *str, t_glob *glob)
{
	
}

void		hub_final(t_glob *glob) // Hub final du traitement globing
{
	FT_INIT(int, i, 0);
	FT_INIT(char *, tmp, NULL);
	while (g_shell.line[i] != ' ')
		i++;
	i++;
	while (g_shell.line[i])
	{
		tmp = next_expr(g_shell.line, i);
		i += ft_strlen(tmp);
		printf("tmp = %s\n", tmp);
		if (ft_strchr(tmp, '{') && ft_strchr(tmp,'}') && glob->cbracket)
		{
			while (glob->cbracket->list->next)
			{
				g_parse_expr(glob->cbracket->list->content, glob);
				glob->cbracket->list = glob->cbracket->list->next;
			}
			g_parse_expr(glob->cbracket->list->content, glob);
			if (glob->cbracket->next)
				glob->cbracket = glob->cbracket->next;
		}
		else
			g_parse_expr(tmp, glob);
		free(tmp);
	}
}
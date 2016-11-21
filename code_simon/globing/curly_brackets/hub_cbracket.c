/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hub_cbracket.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 11:49:29 by sgaudin           #+#    #+#             */
/*   Updated: 2016/11/16 11:49:31 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/globing.h"

int				handle_cbracket(char *line, t_glob *glob)
{
	if (!cbracket_errors(line, glob))
		return (0);
	if (!clist_pushback(&glob->cbracket))
		return (0);
	fill_clist(line);
	return (1);
}

int				hub_cbracket(t_glob *glob)
{
	FT_INIT(int, i, 0);
	FT_INIT(char *, tmp, NULL);
	while (g_shell.line[i])
	{
		if (g_shell.line[i] == '{')
		{
			tmp = ft_strsub(g_shell.line, i,
				next_bracket(g_shell.line, '{', i) + 1);
			printf("tmp = %s\n", tmp);
			if (!handle_cbracket(tmp, glob))
				return (0);
			i += next_bracket(g_shell.line, '{', i);
			free(tmp);
		}
		i++;
	}
	return (1);
}
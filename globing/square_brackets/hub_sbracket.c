/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hub_sbracket.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 17:25:25 by sgaudin           #+#    #+#             */
/*   Updated: 2017/04/13 11:03:34 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/globing.h"

int				fill_bracket_tabs(char *line, t_glob *glob)
{
	FT_INIT(char *, tmp, NULL);
	FT_INIT(char *, ret, NULL);
	tmp = handle_categories(line, glob);
	free(line);
	if (!check_rng(tmp))
	{
		if (tmp)
			ft_strdel(&tmp);
		return (0);
	}
	if (!(ret = fill_mix(tmp)))
	{
		ft_strdel(&tmp);
		return (0);
	}
	bracket_pushback(&glob->sbracket);
	glob->sbracket->content = ret;
	if (tmp)
		ft_strdel(&tmp);
	return (1);
}

void			hub_sbracket(t_glob *glob, char *line)
{
	FT_INIT(int, i, 0);
	FT_INIT(char *, tmp, NULL);
	while (line[i])
	{
		if (line[i] == '[')
		{
			tmp = ft_strsub(line, i, next_bracket(line, '[', i) + 1);
			if (!fill_bracket_tabs(ft_strdup(tmp), glob))
			{
				ft_strdel(&tmp);
				return ;
			}
			i += next_bracket(line, '[', i);
			if (tmp && ft_strlen(tmp) > 1)
				free(tmp);
		}
		i++;
	}
}

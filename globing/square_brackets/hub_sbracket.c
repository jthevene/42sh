/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hub_sbracket.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 11:01:41 by sgaudin           #+#    #+#             */
/*   Updated: 2017/02/13 12:38:33 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/globing.h"

int				fill_bracket_tabs(char *line, t_glob *glob)
{
	FT_INIT(char *, tmp, NULL);
	FT_INIT(char *, tmp2, NULL);
	tmp = handle_categories(line, glob);
	free(line);
	if (!check_rng(tmp))
	{
		tmp2 = ft_strjoin("21sh: no matches found: ", glob->command);
		ft_putendl_fd(tmp2, 2);
		free(tmp2);
		return (0);
	}
	bracket_pushback(&glob->sbracket);
	glob->sbracket->content = fill_mix(tmp);
	if (tmp)
		free(tmp);
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
			tmp = ft_strsub(line, i,
				next_bracket(line, '[', i) + 1);
			fill_bracket_tabs(ft_strdup(tmp), glob);
			i += next_bracket(line, '[', i);
			if (tmp && ft_strlen(tmp) > 1)
				free(tmp);
		}
		i++;
	}
}

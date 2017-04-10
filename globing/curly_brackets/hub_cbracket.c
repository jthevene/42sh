/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hub_cbracket.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 11:20:21 by sgaudin           #+#    #+#             */
/*   Updated: 2017/04/10 14:58:07 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/globing.h"

int				handle_cbracket(char *line, t_glob *glob)
{
	if (!cbracket_errors(line, glob))
		return (0);
	if (!clist_pushback(&glob->cbracket))
		return (0);
	fill_clist(line, glob);
	return (1);
}

int				hub_cbracket(t_glob *glob, char *line)
{
	FT_INIT(int, i, 0);
	FT_INIT(char *, tmp, NULL);
	while (i < (int)ft_strlen(line) && line[i])
	{
		if (line[i] == '{')
		{
			tmp = ft_strdup(line);
			i += ft_strlen(tmp);
			if (is_expansion(tmp))
				if (!hub_expansion(ft_strdup(tmp), glob))
					return (free_triple_str(&tmp, NULL, NULL));
			if (glob->exp)
			{
				ft_strdel(&tmp);
				tmp = ft_strdup(glob->exp);
				ft_strdel(&glob->exp);
			}
			if (!handle_cbracket(tmp, glob))
				return (0);
			ft_strdel(&tmp);
			free_double_tab(&glob->ext_args);
		}
		i++;
	}
	return (1);
}

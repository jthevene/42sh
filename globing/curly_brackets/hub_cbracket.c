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
	fill_clist(line, glob);
	return (1);
}

int				hub_cbracket(t_glob *glob, char *line)
{
	FT_INIT(int, i, 0);
	FT_INIT(char *, tmp, NULL);
	while (line[i])
	{
		if (line[i] == '{')
		{
			tmp = ft_strdup(line);
			i += ft_strlen(tmp);
			hub_expansion(ft_strdup(tmp), glob);
			if (glob->exp)
			{
				free(tmp);
				tmp = ft_strdup(glob->exp);
				free(glob->exp);
				glob->exp = NULL;
			}
			if (!handle_cbracket(tmp, glob))
				return (0);
			free(tmp);
			free_double_tab(&glob->ext_args);
		}
		i++;
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_clist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 11:53:17 by sgaudin           #+#    #+#             */
/*   Updated: 2016/11/18 11:53:18 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/globing.h"
#define FILS_DE_PUTERIE "ls {a{bc{d,e}f{g,h},i},jk{lm{no,p}q{r,s},t}uv}"

void			get_patterns(char *str, t_glob *glob)
{
	if (!ft_strchr(str, '{'))
	{
		clist_list_pushback(&glob->cbracket);
		glob->cbracket->list->content = ft_strdup(str);
		printf("New pattern created : %s\n", glob->cbracket->list->content);
	}
	else
		i_algo_imbricated(ft_strdup(str), glob);
	glob->lastb_count = 1;
}

int				fill_clist(char *line, t_glob *glob)
{
	FT_INIT(char *, tmp, NULL);
	FT_INIT(int, i, 1);
	while (line[i])
	{
		if (next_comma(line, i) == -1)
		{
			tmp = ft_strsub(line, i, ft_strlen(line) - i - 1);
			printf("next_comma 1 = %s\n", tmp);
			get_patterns(tmp, glob);
			break ;
		}
		else
		{
			tmp = ft_strsub(line, i, next_comma(line, i));
			i += next_comma(line, i);
		}
		printf("next_comma 2 = %s\n", tmp);
		get_patterns(tmp, glob);
		free(tmp);
		i++;
	}
	return (1);
}

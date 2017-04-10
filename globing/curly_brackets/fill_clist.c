/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_clist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 17:57:44 by sgaudin           #+#    #+#             */
/*   Updated: 2017/04/10 14:58:09 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/globing.h"

static int		touching_brackets(char *str)
{
	FT_INIT(int, i, 0);
	FT_INIT(int, j, 0);
	while (str[i])
	{
		if (str[i] == '{')
		{
			i += next_bracket(str, '{', i);
			j = i;
			while (str[j])
			{
				if (str[j] == '{')
					return (1);
				j++;
			}
		}
		i++;
	}
	return (0);
}

static char		*special_sub(char *str, int i)
{
	FT_INIT(char *, new, NULL);
	FT_INIT(int, j, i);
	FT_INIT(int, count, 0);
	while (str[j])
	{
		if (str[j] == '{')
			count++;
		else if (str[j] == '}')
		{
			count--;
			if (count == -1)
				break ;
		}
		j++;
	}
	new = ft_strsub(str, i, j - i);
	return (new);
}

static int		start_cbracket(char *str, t_glob *glob)
{
	FT_INIT(int, i, 1);
	while (i < (int)ft_strlen(str) && str[i] && str[i - 1] != '{')
		i++;
	glob->ext_args = recup_ext_args(str);
	return (i);
}

void			get_patterns(char *str, t_glob *glob)
{
	if (!ft_strchr(str, '{'))
	{
		clist_list_pushback(&glob->cbracket);
		glob->cbracket->list->content = expand_pattern(str, glob);
	}
	else
		i_algo_imbricated(ft_strdup(str), glob);
	glob->lastb_count = 1;
}

int				fill_clist(char *line, t_glob *glob)
{
	FT_INIT(char *, tmp, NULL);
	FT_INIT(int, i, start_cbracket(line, glob));
	if (touching_brackets(line))
		return (i_algo_imbricated(ft_strdup(line), glob));
	while (line[i])
	{
		if (next_comma(line, i) == -1)
		{
			tmp = is_bracket_in_exp(line, i) > 1 ? special_sub(line, i)
			: ft_strsub(line, i, end_bracket(line, i));
			get_patterns(tmp, glob);
			free(tmp);
			break ;
		}
		else
		{
			tmp = ft_strsub(line, i, next_comma(line, i));
			i += next_comma(line, i);
		}
		get_patterns(tmp, glob);
		free(tmp);
		i++;
	}
	return (1);
}

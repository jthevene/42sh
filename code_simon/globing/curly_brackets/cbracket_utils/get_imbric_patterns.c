/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_imbric_patterns.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 14:28:07 by sgaudin           #+#    #+#             */
/*   Updated: 2016/11/25 14:28:08 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/globing.h"

t_clist				*i_recup_multi_patterns(char *str)
{
	FT_INIT(t_clist *, clist, NULL);
	FT_INIT(int, i, -1);
	FT_INIT(int, j, 0);
	while (str[++i])
	{
		if (str[i] == '{')
		{
			j = i + 1;
			if (!(clist_pushback(&clist)))
				return (0);
			while (str[i] && str[i] != '}')
			{
				if (str[i] == ',' || str[i + 1] == '}')
				{
					if (!(clist_list_pushback(&clist)))
						return (0);
					clist->list->content = str[i] == ',' 
					? ft_strsub(str, j, i - j) : ft_strsub(str, j, i - j + 1);
					j = i + 1;
				}
				i++;
			}
		}
	}
	return (clist);
}

void				i_simple_patterns(char *str, t_glob *glob)
{
	FT_INIT(int, i, 0);
	FT_INIT(int, j, 0);
	while (str[i])
	{
		if (str[i] == ',')
		{
			clist_list_pushback(&glob->cbracket);
			glob->cbracket->list->content = ft_strsub(str, j, i - j);
			j = i + 1;
		}
		i++;
	}
	clist_list_pushback(&glob->cbracket);
	glob->cbracket->list->content = ft_strsub(str, j, i - j);
}

void				i_multi_patterns(char *str, t_glob *glob)
{
/*
	static int		base_nb = count_imbric(str);
	static t_clist	*multi = NULL;
	static int		nb = 0;

	FT_INIT(char *, tmp, NULL);
	if (!multi)
	{
		multi = i_recup_multi_patterns(str);
		rewind_tclist(&multi);
	}
*/
// INSERER RECURSIVE ICI
}

void				i_hub_patterns(char *str, t_glob *glob)
{
//	FT_INIT(char *, tmp, NULL);
	printf("new_str = %s\n", str);
	if (!ft_strchr(str, '{'))
		i_simple_patterns(str, glob);
	else
	{
		if (!detect_double_bracket(str))
			i_multi_patterns(ft_strdup(str), glob);
	}
	free(str);
//	print_clist_list(&glob->cbracket);
}
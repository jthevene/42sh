/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imbric_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 19:33:37 by sgaudin           #+#    #+#             */
/*   Updated: 2017/04/10 14:58:13 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/globing.h"

t_clist			*i_recup_multi_patterns(char *str, int i, int j)
{
	FT_INIT(t_clist *, clist, NULL);
	FT_INIT(int, index, -1);
	while (str[++i])
	{
		if (str[i] == '{')
		{
			j = i + 1;
			if (!(clist_pushback(&clist)))
				return (0);
			clist->index = ++index;
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

int				i_detect_imbric(char *str)
{
	FT_INIT(int, i, 0);
	FT_INIT(int, j, 0);
	FT_INIT(int, count, 0);
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '{')
		{
			j = i + 1;
			count = 0;
			while (str[j] != '}')
			{
				if (str[j] == '{')
					return (count);
				count++;
				j++;
			}
		}
		i++;
	}
	return (-1);
}

char			*expand_pattern(char *pat, t_glob *glob)
{
	FT_INIT(char *, tmp, NULL);
	FT_INIT(char *, ret, NULL);
	if (!glob->ext_args[0] && !glob->ext_args[1])
		ret = ft_strdup(pat);
	else
	{
		tmp = glob->ext_args[0] ? ft_strjoin(glob->ext_args[0], pat) : NULL;
		if (glob->ext_args[1])
			ret = tmp ? ft_strjoin(tmp, glob->ext_args[1])
			: ft_strjoin(pat, glob->ext_args[1]);
		else
			ret = ft_strdup(tmp);
	}
	if (tmp)
		free(tmp);
	return (ret);
}

void			rewind_index(t_clist **list, int index)
{
	while ((*list)->prev)
		(*list) = (*list)->prev;
	while ((*list) && (*list)->index != index)
		(*list) = (*list)->next;
}

int				count_imbric(char *str)
{
	FT_INIT(int, i, 0);
	FT_INIT(int, count, 0);
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '{')
			count++;
		i++;
	}
	return (count);
}

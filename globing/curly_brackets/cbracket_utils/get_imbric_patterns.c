/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_imbric_patterns.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 19:35:00 by sgaudin           #+#    #+#             */
/*   Updated: 2017/04/10 14:58:17 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/globing.h"

char				*i_multi_patterns2(t_clist **multi, int index)
{
	FT_INIT(char *, tmp, NULL);
	FT_INIT(char *, tmp2, NULL);
	FT_INIT(char *, tmp3, NULL);
	tmp2 = i_multi_patterns(multi, index + 1);
	rewind_index(multi, index);
	if (!tmp2)
	{
		if (!(*multi)->list->next)
		{
			rewind_tbracket(&(*multi)->list);
			return (NULL);
		}
		else
			(*multi)->list = (*multi)->list->next;
		tmp2 = i_multi_patterns(multi, index + 1);
	}
	rewind_index(multi, index);
	tmp = ft_strdup((*multi)->list->content);
	tmp3 = ft_strjoin(tmp, tmp2);
	free(tmp);
	free(tmp2);
	return (tmp3);
}

char				*i_multi_patterns(t_clist **multi, int index)
{
	FT_INIT(char *, tmp, NULL);
	while ((*multi) && (*multi)->index != index)
		(*multi) = (*multi)->next;
	if (!(*multi)->next)
	{
		if (!(*multi)->list->next)
		{
			if ((*multi)->rewind == TRUE)
			{
				rewind_tbracket(&(*multi)->list);
				(*multi)->rewind = FALSE;
				return (NULL);
			}
			tmp = ft_strdup((*multi)->list->content);
			(*multi)->rewind = TRUE;
			return (tmp);
		}
		else
		{
			(*multi)->list = (*multi)->list->next;
			return (ft_strdup((*multi)->list->prev->content));
		}
	}
	return (i_multi_patterns2(multi, index));
}

void				i_simple_patterns(char *str, t_glob *glob)
{
	FT_INIT(int, i, 0);
	FT_INIT(int, j, 0);
	FT_INIT(char *, tmp, NULL);
	while (str[i])
	{
		if (str[i] == ',')
		{
			clist_list_pushback(&glob->cbracket);
			tmp = ft_strsub(str, j, i - j);
			glob->cbracket->list->content = expand_pattern(tmp, glob);
			j = i + 1;
			free(tmp);
		}
		i++;
	}
	clist_list_pushback(&glob->cbracket);
	tmp = ft_strsub(str, j, i - j);
	glob->cbracket->list->content = expand_pattern(tmp, glob);
	free(tmp);
}

t_clist				*i_create_multi_list(char *str)
{
	FT_INIT(t_clist *, multi, NULL);
	multi = i_recup_multi_patterns(str, -1, 0);
	rewind_tclist(&multi);
	free(str);
	return (multi);
}

void				i_hub_patterns(char *str, t_glob *glob)
{
	FT_INIT(char *, tmp, NULL);
	FT_INIT(int, count, 0);
	FT_INIT(t_clist *, multi, NULL);
	if (!str || !glob)
		return ;
	if (!ft_strchr(str, '{'))
		i_simple_patterns(str, glob);
	else
	{
		if (i_detect_imbric(str) == -1)
		{
			multi = i_create_multi_list(ft_strdup(str));
			while ((tmp = i_multi_patterns(&multi, 0)))
			{
				clist_list_pushback(&glob->cbracket);
				glob->cbracket->list->content = expand_pattern(tmp, glob);
				count++;
				free(tmp);
			}
			free_tclist(&multi);
		}
		else
			i2_hub_imbric(ft_strdup(str), 0, glob);
	}
	free(str);
}

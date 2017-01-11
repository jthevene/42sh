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

char				*i_multi_patterns(t_clist **multi, int index)
{
	FT_INIT(char *, tmp, NULL);
	FT_INIT(char *, tmp2, NULL);
	FT_INIT(char *, tmp3, NULL);
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
//			printf("New pattern created : %s\n", glob->cbracket->list->content);
			j = i + 1;
			free(tmp);
		}
		i++;
	}
	clist_list_pushback(&glob->cbracket);
	tmp = ft_strsub(str, j, i - j);
	glob->cbracket->list->content = expand_pattern(tmp, glob);
//	printf("New pattern created : %s\n", glob->cbracket->list->content);
	free(tmp);
}

t_clist				*i_create_multi_list(char *str)
{
	FT_INIT(t_clist *, multi, NULL);
	multi = i_recup_multi_patterns(str);
	rewind_tclist(&multi);
	free(str);
	return (multi);
}

void				i_hub_patterns(char *str, t_glob *glob)
{
	FT_INIT(char *, tmp, NULL);
	FT_INIT(int, count, 0);
	FT_INIT(t_clist *, multi, NULL);
//	printf("new_str = %s\n\n", str);
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
//				printf("%d - New pattern created : %s\n\n", count, glob->cbracket->list->content);
				count++;
				free(tmp);
			}
			free_tclist(&multi);
		}
		else
			i2_hub_imbric(ft_strdup(str), glob);
	}
	free(str);
}

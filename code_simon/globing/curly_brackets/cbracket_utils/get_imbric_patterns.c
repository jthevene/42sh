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

char				*i_multi_patterns(char *str, int index)
{
	static t_clist*	multi[] = {NULL};
	static int		alrdy_bis[] = {0};
	static int		init = 0;
	static int		alrdy = 0;

	FT_INIT(int, count, count_imbric(str));
	FT_INIT(char *, tmp, NULL);
	FT_INIT(char *, tmp2, NULL);
	FT_INIT(char *, tmp3, NULL);
	if (!init)
	{
		ft_putendl("Initializing");
		while (index < count)
		{
			tmp = ft_strdup(str);
			multi[index] = i_recup_multi_patterns(str);
			free(str);
			str = i_next_bracket(tmp);
			free(tmp);
			multi[index]->test = index;
			rewind_tclist(&multi[index]);
			alrdy_bis[index] = 0;
			index++;
		}
		free(str);
		multi[index] = NULL;
		index = 0;
		init = 1;
	}
	printf("Index = %d\n", index);
	printf("Index test = %d\n", multi[index]->test);
	ft_putendl("TEST DEBUT");
	if (!multi[index]->next)
	{
		ft_putendl("TRAITEMENT LAST LIST");
		if (!multi[index]->list->next)
		{
			if (!alrdy)
			{
				tmp = ft_strdup(multi[index]->list->content);
				alrdy = 1;
			}
			else
			{
				rewind_tbracket(&multi[index]->list);
				alrdy = 0;
				tmp = NULL;
			}
			return (tmp);
		}
		else
		{
			multi[index]->list = multi[index]->list->next;
			return (ft_strdup(multi[index]->list->prev->content));
		}
	}
	if (!multi[index]->list->next)
	{
		ft_putendl("TRAITEMENT !LIST->NEXT INTERMEDIAIRE");
		if (!alrdy)
		{
			tmp = ft_strdup(multi[index]->list->content);
			alrdy = 1;
		}
		else
		{
			rewind_tbracket(&multi[index]->list);
			alrdy = 0;
			return (NULL);
		}
	}
	else
	{
		ft_putendl("TRAITEMENT LIST->NEXT INTERMEDIAIRE");
		tmp2 = i_multi_patterns(str, index + 1);
		ft_putendl("Recursive ended properly");
		if (!tmp2)
			multi[index]->list = multi[index]->list->next;
		if (!multi[index]->list->next)
			alrdy = 1;
		tmp = ft_strdup(multi[index]->list->content);
	}
	tmp2 = i_multi_patterns(str, index + 1);
	tmp3 = ft_strjoin(tmp, tmp2);
	free(tmp);
	free(tmp2);
	return (tmp3);
}

void				i_hub_patterns(char *str, t_glob *glob)
{
	FT_INIT(char *, tmp, NULL);
	printf("new_str = %s\n", str);
	if (!ft_strchr(str, '{'))
		i_simple_patterns(str, glob);
	else
	{
		if (!detect_double_bracket(str))
		{
			while ((tmp = i_multi_patterns(ft_strdup(str), 0)))
			{
				printf("RESULT RECURSIVE = %s\n", tmp);
				free(tmp);
			}
		}
	}
	free(str);
//	print_clist_list(&glob->cbracket);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_sentence.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvirgile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 17:19:59 by dvirgile          #+#    #+#             */
/*   Updated: 2017/01/16 17:20:05 by dvirgile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/42sh.h"

void		free_simple_tab(char ***tab_to_del)
{
	int		colonne;

	colonne = 0;
	while ((*tab_to_del) && (*tab_to_del)[colonne])
	{
		free((*tab_to_del)[colonne]);
		(*tab_to_del)[colonne] = NULL;
		colonne++;
	}
	free(*tab_to_del);
	*tab_to_del = NULL;
}

char		*set_sentence(char *str, int len_str, char *name)
{
	FT_INIT(char*, tmp, ft_itoa(len_str + 2));
	str = ft_strcat(str, "%-");
	str = ft_strcat(str, tmp);
	str = ft_strcat(str, "s");
	ft_printf(str, name);
	ft_bzero(str, ft_strlen(str));
	ft_strdel(&tmp);
	return (str);
}

char		*is_space(char *sentence, char *str)
{
	FT_INIT(char*, tmp, str);
	if (sentence[ft_strlen(sentence) - 1] == ' ')
	{
		str = ft_strjoin(str, " ");
		ft_strdel(&tmp);
	}
	ft_strdel(&sentence);
	return (str);
}

char		*default_sentence(char **sentence)
{
	FT_INIT(char **, path, NULL);
	FT_INIT(int, i, 0);
	FT_INIT(char*, tmp, NULL);
	FT_INIT(char*, str, ft_strdup(""));
	if (!ft_strchr(*sentence, ' '))
		return (*sentence);
	path = ft_strsplit(*sentence, ' ');
	while (path && path[i])
	{
		tmp = str;
		str = ft_strjoin(str, path[i]);
		if (tmp)
			ft_strdel(&tmp);
		if (path[i + 1] && str && ft_strlen(str))
		{
			tmp = str;
			str = ft_strjoin(str, " ");
			if (tmp)
				ft_strdel(&tmp);
		}
		i++;
	}
	free_simple_tab(&path);
	str = is_space(*sentence, str);
	return (str);
}

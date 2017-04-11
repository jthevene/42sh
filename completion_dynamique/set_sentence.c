/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_sentence.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvirgile <dvirgile@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:36:40 by hjacque           #+#    #+#             */
/*   Updated: 2017/04/11 12:18:15 by dvirgile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh42.h"

char		*str_to_search(char *sentence)
{
	FT_INIT(char*, new_sentence, NULL);
	if (!sentence)
		return (NULL);
	if (ft_strchr(sentence, ' '))
		sentence = ft_strrchr(sentence, ' ') + 1;
	if (ft_strrchr(sentence, '/'))
	{
		new_sentence = ft_strrchr(sentence, '/') + 1;
		if (ft_strlen(new_sentence))
			return (new_sentence);
		else
			return ("");
	}
	else
		new_sentence = sentence;
	return (new_sentence);
}

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
	len_str += 2;
	ft_putstr(name);
	while ((len_str-- - ft_strlen(name)) > 0)
		ft_putchar(' ');
	(void)name;
	ft_bzero(str, ft_strlen(str));
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
	FT_INIT(char*, str, NULL);
	if (!sentence || !(*sentence) || !ft_strchr(*sentence, ' '))
		return (*sentence);
	str = ft_strdup("");
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
			ft_strdel(tmp ? &tmp : NULL);
		}
		i++;
	}
	free_simple_tab(&path);
	str = is_space(*sentence, str);
	return (str);
}

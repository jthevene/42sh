/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjacque <hjacque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:36:40 by hjacque           #+#    #+#             */
/*   Updated: 2017/03/08 14:46:39 by hjacque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh42.h"

static t_file		*get_values(t_file *match_files)
{
	FT_INIT(t_file*, head, match_files);
	FT_INIT(int, nb_elem, 0);
	FT_INIT(int, len_str, 0);
	if (!match_files)
		return (NULL);
	while (match_files)
	{
		nb_elem++;
		len_str = match_files->len > len_str ? match_files->len : len_str;
		match_files = match_files->next;
	}
	head->len = len_str;
	head->nb_elem = nb_elem;
	return (head);
}

static	int			verif_matchs(t_file *files, size_t len_cmp, int nb_args)
{
	FT_INIT(t_file*, before, files);
	FT_INIT(t_file*, after, before->next);
	FT_INIT(int, i, 1);
	if (nb_args == 1 && len_cmp < ft_strlen(files->name))
		return (1);
	while (before && before->next)
	{
		if (!ft_strncmp(before->name, after->name, len_cmp))
			i++;
		else
			break ;
		before = before->next;
		after = before->next;
	}
	if (i == nb_args)
		return (1);
	return (0);
}

static char			*set_similarity(char *similarity, char *sentence)
{
	FT_INIT(char*, tmp, NULL);
	if (similarity && ft_strlen(similarity))
	{
		tmp = similarity;
		similarity = ft_strdup(similarity + ft_strlen(sentence));
		ft_strdel(&tmp);
		if (similarity && sentence && !ft_strcmp(similarity, sentence))
			ft_strdel(&similarity);
	}
	else
	{
		ft_strdel(&similarity);
		similarity = ft_strdup(sentence);
	}
	return (similarity);
}

char				*similarity(t_file *match_files, char *sentence)
{
	FT_INIT(int, len_cmp, ft_strlen(sentence));
	FT_INIT(char*, similarity, ft_strnew(match_files->len * 2));
	FT_INIT(int, nb_args, match_files->nb_elem);
	FT_INIT(int, verif, nb_args);
	while (verif && len_cmp <= match_files->len)
	{
		verif = verif_matchs(match_files, len_cmp, nb_args);
		if (verif)
			ft_strncpy(similarity, match_files->name, len_cmp);
		len_cmp++;
	}
	similarity = set_similarity(similarity, sentence);
	if (similarity && !ft_strlen(similarity))
	{
		ft_strdel(&similarity);
		similarity = "";
	}
	return (similarity);
}

t_file				*compare_list_sentence(t_file *files, char *sentence)
{
	FT_INIT(t_file*, match_files, NULL);
	FT_INIT(t_file*, head, NULL);
	while (files)
	{
		if (files && ft_strlen(sentence) <= ft_strlen(files->name) &&
			!ft_strncmp(files->name, sentence, ft_strlen(sentence)))
		{
			if ((files->name)[0] != '.' || ft_strcmp(sentence, ""))
			{
				if (!match_files)
					MULTI(head, match_files, files);
				else
				{
					match_files->next = files;
					match_files = match_files->next;
				}
			}
		}
		files = files->next;
	}
	if (match_files)
		match_files->next = NULL;
	head = get_values(head);
	return (head);
}

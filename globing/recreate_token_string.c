/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recreate_token_string.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 10:32:10 by sgaudin           #+#    #+#             */
/*   Updated: 2017/04/10 14:57:30 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/globing.h"

static int		supp_squote_globing(char **line, int pos, int s)
{
	s = pos;
	ft_memmove(&((*line)[s]), \
		&((*line)[s + 1]), ft_strlen((*line)) - s);
	while ((*line)[pos] != '\'')
		pos++;
	ft_memmove(&((*line)[pos]), \
		&((*line)[pos + 1]), ft_strlen((*line)) - pos);
	pos++;
	return (pos);
}

static int		supp_dquote_globing(char **line, int pos, int d)
{
	d = pos;
	ft_memmove(&((*line)[d]), \
		&((*line)[d + 1]), ft_strlen((*line)) - d);
	while ((*line)[pos] != '\"')
		pos++;
	ft_memmove(&((*line)[pos]), \
		&((*line)[pos + 1]), ft_strlen((*line)) - pos);
	pos++;
	return (pos);
}

int				backslash_char_globing(char **line)
{
	FT_INIT(int, pos, 0);
	FT_INIT(int, s, 0);
	FT_INIT(int, d, 0);
	while ((*line)[pos])
	{
		if ((*line)[pos] == '\'')
			pos = supp_squote_globing(line, pos, s);
		else if ((*line)[pos] == '\"')
			pos = supp_dquote_globing(line, pos, d);
		else if ((*line)[pos] == '\\')
		{
			ft_memmove(&((*line)[pos]), \
				&((*line)[pos + 1]), ft_strlen((*line)) - pos);
			pos++;
		}
		pos++;
	}
	return (0);
}

static int		start_recreate(char **ret, t_glob *glob)
{
	rewind_tbracket(&glob->args);
	(*ret) = ft_strdup(glob->args->content);
	if (glob->args->next)
	{
		glob->args = glob->args->next ? glob->args->next : glob->args;
		return (1);
	}
	else
		return (0);
}

char			*recreate_token_string(t_glob *glob)
{
	FT_INIT(char *, ret, NULL);
	FT_INIT(char *, tmp, NULL);
	FT_INIT(char *, tmp2, NULL);
	if (!glob->args)
		return (NULL);
	if (!start_recreate(&ret, glob))
	{
		free_tbracket(&glob->args);
		return (ret);
	}
	while (glob->args != NULL)
	{
		tmp = ft_strdup(ret);
		ft_strdel(&ret);
		tmp2 = ft_strjoin(tmp, " ");
		ft_strdel(&tmp);
		ret = ft_strjoin(tmp2, glob->args->content);
		ft_strdel(&tmp2);
		if (!glob->args->next)
			break ;
		glob->args = glob->args->next;
	}
	free_tbracket(&glob->args);
	return (ret);
}

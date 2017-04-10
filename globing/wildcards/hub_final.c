/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hub_final.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 19:52:06 by sgaudin           #+#    #+#             */
/*   Updated: 2017/04/10 14:57:46 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/globing.h"

int			is_only_token(char token, char *str)
{
	FT_INIT(int, i, 0);
	if (!ft_strchr(str, token))
		return (0);
	while (str[i])
	{
		if (str[i] != token)
			return (0);
		if (str[i] == '[')
			i += next_bracket(str, '[', i);
		i++;
	}
	return (1);
}

int			g_no_token(char *str, t_glob *glob)
{
	if (!bracket_pushback(&glob->args))
		return (0);
	glob->args->content = ft_strdup(str);
	return (1);
}

int			only_star(char *str, t_glob *glob)
{
	FT_INIT(char *, path, get_cmd_path(str));
	FT_INIT(t_lst *, files, get_dir_content(!path ? "./" : path));
	while (files)
	{
		if (ft_strcmp(files->content, ".") && ft_strcmp(files->content, ".."))
			pushback_content(&glob->args, ft_strdup(files->content));
		if (!files->next)
			break ;
		files = files->next;
	}
	ft_lst_free(&files);
	return (0);
}

int			multi_handling(t_glob *glob)
{
	FT_INIT(t_bracket *, tmp, NULL);
	rewind_tbracket(&glob->args);
	while (glob && glob->args && glob->args->content
		&& (ft_strchr(glob->args->content, '*')
		|| ft_strchr(glob->args->content, '?')
		|| ft_strchr(glob->args->content, '[')))
	{
		copy_list(&glob->args, &tmp);
		free_tbracket(&glob->args);
		while (tmp->next)
		{
			g_parse_expr(tmp->content, glob);
			tmp = tmp->next;
		}
		g_parse_expr(tmp->content, glob);
		free_tbracket(&tmp);
	}
	return (1);
}

int			hub_final(t_glob *g, char *line)
{
	FT_INIT(int, i, 0);
	FT_INIT(char *, tmp, NULL);
	rewind_tbracket(g->cbracket ? &g->cbracket->list : NULL);
	while (line[i])
	{
		tmp = ft_strdup(line);
		i += ft_strlen(tmp);
		if (ft_strchr(tmp, '{') && ft_strchr(tmp, '}') && g->cbracket)
		{
			while (g->cbracket->list->next)
			{
				g_parse_expr(g->cbracket->list->content, g);
				g->cbracket->list = g->cbracket->list->next;
			}
			g_parse_expr(g->cbracket->list->content, g);
			g->cbracket = g->cbracket->next ? g->cbracket->next : g->cbracket;
		}
		else
			g_parse_expr(tmp, g);
		ft_memdel((void *)&tmp);
		if ((i + 1) < (int)ft_strlen(line) && !line[i + 1])
			break ;
	}
	return (!g->args ? 0 : multi_handling(g));
}

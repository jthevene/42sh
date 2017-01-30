/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hub_final.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 09:37:08 by sgaudin           #+#    #+#             */
/*   Updated: 2016/12/07 09:37:09 by sgaudin          ###   ########.fr       */
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
	FT_INIT(t_lst *, files, get_dir_content(path));
	while (files)
	{
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
	if (!glob->args)
		return (0);
	rewind_tbracket(&glob->args);
	while (ft_strchr(glob->args->content, '*')
		|| ft_strchr(glob->args->content, '?')
		|| ft_strchr(glob->args->content, '['))
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

void		hub_final(t_glob *g)
{
	FT_INIT(int, i, 0);
	FT_INIT(char *, tmp, NULL);
	while (g_shell.line[i] && g_shell.line[i] != ' ')
		i++;
	i++;
	rewind_tbracket(g->cbracket ? &g->cbracket->list : NULL);
	while (g_shell.line[i])
	{
		tmp = next_expr(g_shell.line, i);
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
		if (!g_shell.line[i + 1])
			break ;
	}
//	multi_handling(g);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 21:03:02 by sgaudin           #+#    #+#             */
/*   Updated: 2016/12/07 21:03:03 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/globing.h"

int			only_qmark(char *str, t_glob *glob)
{
	if (str && glob)
		return (1);
	return (0);
}

void		only_cbrkt2(int i, int len, t_lst *f, t_glob *g)
{
	while (++i < len)
	{
		if (ft_strchr(g->sbracket->content, ((char*)f->content)[i]))
			g->sbracket = g->sbracket->next ? g->sbracket->next : g->sbracket;
		else
			break ;
	}
	if (i == len)
		push_content_path(&g->args, ft_strdup(f->content), g);
}

int			only_cbrkt(char *str, t_glob *g)
{
	g->f_path = get_cmd_path(str);
	g->l_path = get_cmd_last_path(str);
	FT_INIT(int, len, get_len_token(str));
	FT_INIT(t_lst *, f, get_dir_content(g->f_path));
	FT_INIT(int, i, -1);
	hub_sbracket(g, str);
	rewind_tbracket(&g->sbracket);
	while (f)
	{
		if ((int)ft_strlen(f->content) == len)
		{
			only_cbrkt2(i, len, f, g);
			rewind_tbracket(&g->sbracket);
			i = -1;
		}
		if (!f->next)
			break ;
		f = f->next;
	}
	free_double_str(&g->f_path, &g->l_path);
	free_tbracket(&g->sbracket);
	ft_lst_free(&f);
	return (0);
}

int			mix_with_star(char *str, t_glob *glob)
{
	glob->f_path = get_cmd_path(str);
	glob->l_path = get_cmd_last_path(str);
	FT_INIT(char *, token, get_token(str));
	FT_INIT(t_lst *, files, get_dir_content(glob->f_path));
	hub_sbracket(glob, token);
	rewind_tbracket(&glob->sbracket);
	while (files)
	{
		check_file(ft_strlen(files->content), token, files->content, &glob);
		if (!files->next)
			break ;
		files = files->next;
	}
	if (glob->f_path)
		free(glob->f_path);
	if (glob->l_path)
		free(glob->l_path);
	if (token)
		free(token);
	free_tbracket(&glob->sbracket);
	ft_lst_free(&files);
	return (0);
}

int			mix_token(char *str, t_glob *glob)
{
	glob->f_path = get_cmd_path(str);
	glob->l_path = get_cmd_last_path(str);
	FT_INIT(char *, token, get_token(str));
	FT_INIT(t_lst *, files, get_dir_content(glob->f_path));
	FT_INIT(int, len, get_len_token(token));
	hub_sbracket(glob, token);
	rewind_tbracket(&glob->sbracket);
	while (files)
	{
		if ((int)ft_strlen(files->content) == len)
			check_file(len, token, files->content, &glob);
		rewind_tbracket(&glob->sbracket);
		if (!files->next)
			break ;
		files = files->next;
	}
	if (glob->f_path)
		free(glob->f_path);
	if (glob->l_path)
		free(glob->l_path);
	if (token)
		free(token);
	free_tbracket(&glob->sbracket);
	ft_lst_free(&files);
	return (0);
}

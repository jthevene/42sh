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

int			g_no_token(char *str, t_glob *glob)
{
	if (!bracket_pushback(&glob->args))
		return (0);
	glob->args->content = ft_strdup(str);
//	printf("Création d'argument : %s\n", glob->args->content);
	return (1);
}

int			only_qmark(char *str, t_glob *glob)
{
//	FT_INIT(int, len, ft_strlen(str));
//	printf("LEN ARG QMARK : %d\n", len);
	if (str && glob)
		return (1);
	return (0);
}

int			only_cbrkt(char *str, t_glob *glob)
{
	glob->f_path = get_cmd_path(str);
	glob->l_path = get_cmd_last_path(str);
	FT_INIT(int, len, get_len_token(str));
	FT_INIT(t_lst *, files, get_dir_content(glob->f_path));
	FT_INIT(int, i, -1);
	hub_sbracket(glob, str);
	rewind_tbracket(&glob->sbracket);
	while (files)
	{
		if ((int)ft_strlen(files->content) == len)
		{
			while (++i < len)
			{
				if (ft_strchr(glob->sbracket->content, ((char *)files->content)[i]))
					glob->sbracket = glob->sbracket->next ? glob->sbracket->next : glob->sbracket;
				else
					break ;
			}
			if (i == len)
			{
				push_content_path(&glob->args, ft_strdup(files->content), glob);
//				printf("Création d'argument : %s\n", glob->args->content);
			}
			rewind_tbracket(&glob->sbracket);
			i = -1;
		}
		if (!files->next)
			break ;
		files = files->next;
	}
	if (glob->f_path)
		free(glob->f_path);
	if (glob->l_path)
		free(glob->l_path);
	free_tbracket(&glob->sbracket);
	/* FREE FILES */
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
//	printf("\n/*** MIX_WITH_STAR ***/\nF_PATH = %s\nL_PATH = %s\nTOKEN = %s\n\n", glob->f_path, glob->l_path, token);
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
	free_tbracket(&glob->sbracket);
	/* FREE FILES */
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
//	printf("\n/*** MIX_TOKEN ***/\nF_PATH = %s\nL_PATH = %s\nTOKEN = %s\n\n", glob->f_path, glob->l_path, token);
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
	free_tbracket(&glob->sbracket);
	/* FREE FILES */
	return (0);
}
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
	printf("NO TOKEN\n");
	glob->args->content = ft_strdup(str);
	return (1);
}

int			only_qmark(char *str, t_glob *glob)
{
	FT_INIT(int, len, ft_strlen(str));
	printf("LEN ARG QMARK : %d\n", len);
	if (glob)
		return (1);
	return (0);
}

int			only_cbrkt(char *str, t_glob *glob)
{
	FT_INIT(int, len, get_len_token(str));
	FT_INIT(char *, path, get_cmd_path(str));
	FT_INIT(t_list *, files, get_dir_content(path));
	FT_INIT(int, i, -1);
	hub_sbracket(glob, str);
	rewind_tbracket(&glob->sbracket);
	while (files)
	{
		if ((int)ft_strlen(files->content) == len)
		{
			while (++i < len)
			{
				if (ft_strchr(glob->sbracket->content, files->content[i]))
					glob->sbracket = glob->sbracket->next ? glob->sbracket->next : glob->sbracket;
				else
					break ;
			}
			if (i == len)
			{
				pushback_content(&glob->args, ft_strdup(files->content));
				printf("Création d'argument : %s\n", glob->args->content);
			}
			rewind_tbracket(&glob->sbracket);
			i = -1;
		}
		if (!files->next)
			break ;
		files = files->next;
	}
	free(path);
	free_tbracket(&glob->sbracket);
	/* FREE FILES */
	return (0);
}

int			mix_with_star(char *str, t_glob *glob)
{
	FT_INIT(char *, path, get_cmd_path(str));
	FT_INIT(t_list *, files, get_dir_content(path));
	ft_print_list_content(files);
	free(path);
	if (str && glob)
		return (1);
	return (0);
}

int			mix_token(char *str, t_glob *glob)
{
	FT_INIT(char *, path, get_cmd_path(str));
	FT_INIT(char *, token, get_token(str));
	FT_INIT(t_list *, files, get_dir_content(path));
	FT_INIT(int, len, get_len_token(token));
	FT_INIT(int, i, -1);
	FT_INIT(int, j, -1);
	hub_sbracket(glob, token);
	rewind_tbracket(&glob->sbracket);
	printf("/*** MIX_TOKEN ***/\nLEN = %d\nPATH = %s\nTOKEN = %s\n", len, path, token);
	while (files)
	{
		if ((int)ft_strlen(files->content) == len)
		{
			while (++j < len)
			{
				if (token[++i] == '[' && ft_strchr(glob->sbracket->content, files->content[j]))
				{
					glob->sbracket = glob->sbracket->next ? glob->sbracket->next : glob->sbracket;
					i += next_bracket(token, '[', i);
				}
				else if (token[i] != '?' && token[i] != '[' && files->content[j] != token[i])
					break ;
			}
			if (j == len)
			{
				pushback_content(&glob->args, ft_strdup(files->content));
				printf("Création d'argument : %s\n", glob->args->content);
			}
		}
		rewind_tbracket(&glob->sbracket);
		i = -1;
		j = -1;
		if (!files->next)
			break ;
		files = files->next;
	}
	free(path);
	free_tbracket(&glob->sbracket);
	return (0);
}
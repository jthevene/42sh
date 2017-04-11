/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_auto_completion.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvirgile <dvirgile@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:36:40 by hjacque           #+#    #+#             */
/*   Updated: 2017/04/11 12:18:51 by dvirgile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh42.h"

t_file			*get_file_path(char *path, char *sentence)
{
	DIR			*rep;

	FT_INIT(t_file*, files, NULL);
	if (!path || !sentence)
		return (NULL);
	FT_INIT(char*, var_path, get_var(g_shell.env, "PATH"));
	rep = opendir(path);
	if (rep && !ft_strchr(sentence, ' ')
		&& sentence[0] != '/' && var_path)
		files = store_files_dirs(rep, files, path, str_to_search(sentence));
	else if (rep && path && sentence[ft_strlen(sentence) - 1] != ' ')
		files = store_files_dirs(rep, files, path, str_to_search(sentence));
	else
	{
		closedir(rep);
		if ((rep = opendir(".")))
			files = store_files_dirs(rep, files,
				path, str_to_search(sentence));
	}
	closedir(rep);
	free(var_path);
	return (files);
}

static t_file	*files_list(char **sentence, bool detect_bins)
{
	FT_INIT(char**, path, NULL);
	FT_INIT(t_file*, files, NULL);
	FT_INIT(t_file*, head, NULL);
	FT_INIT(int, i, 0);
	FT_INIT(char*, home, get_var(g_shell.env, "HOME"));
	FT_INIT(char*, pwd, getcwd(NULL, 1024));
	*sentence = default_sentence(sentence);
	path = set_path(sentence, home, pwd, detect_bins);
	while (path && path[i])
	{
		if (!files)
			MULTI(head, files, get_file_path(path[i], *sentence));
		else
			files->next = get_file_path(path[i], *sentence);
		while (files && files->next)
			files = files->next;
		i++;
	}
	free_tab(path);
	free(home);
	free(pwd);
	head = sort_list(head);
	return (head);
}

static char		*if_new_sentence(char *sentence, t_file *files,
								char *new_sentence)
{
	FT_INIT(int, i, 0);
	ft_strdel(&sentence);
	free_files(&files);
	while (new_sentence[i])
	{
		fill_current_line(new_sentence[i++]);
		g_shell.cursor_x++;
	}
	ft_strdel(&new_sentence);
	return (g_shell.current_line);
}

static char		*get_similaryties(char *sentence, t_file *match_files
								, char *to_search)
{
	FT_INIT(char*, similarity_val, NULL);
	similarity_val = similarity(match_files, to_search);
	if (sentence && !ft_strchr(sentence, ' ') && !ft_strcmp(sentence, ".") &&
	similarity_val && !((int)ft_strlen(similarity_val)))
	{
		fill_current_line('/');
		g_shell.cursor_x++;
	}
	return (similarity_val);
}

char			*detect_auto_completion(char *sentence, bool detect_bins)
{
	static int check = 0;

	FT_INIT(t_file*, files, NULL);
	FT_INIT(t_file*, match_files, NULL);
	FT_INIT(char*, new_sentence, NULL);
	FT_INIT(char*, to_search, NULL);
	if (!sentence || !ft_strlen(sentence) || !verif_sentence(sentence))
		return (sentence);
	FT_INIT(char*, copy_sentence, set_copy_sentence(sentence));
	files = files_list(&copy_sentence, detect_bins);
	to_search = str_to_search(copy_sentence);
	if ((match_files = compare_list_sentence(files, to_search)))
		new_sentence = get_similaryties(sentence, match_files, to_search);
	if (new_sentence && ft_strlen(new_sentence))
	{
		check = 0;
		return (if_new_sentence(copy_sentence, files, new_sentence));
	}
	if (check != prev_sentence_value(sentence))
		check = prev_sentence_value(sentence);
	display_completion(copy_sentence, match_files);
	if (copy_sentence)
		ft_strdel(&copy_sentence);
	return (sentence);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_auto_completion.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 17:17:47 by dvirgile          #+#    #+#             */
/*   Updated: 2017/02/13 12:38:50 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

static char		*str_to_search(char *sentence)
{
	FT_INIT(char*, new_sentence, NULL);
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

t_file			*get_file_path(char *path, char *sentence)
{
	DIR			*rep;

	FT_INIT(t_file*, files, NULL);
	if (!path || !sentence)
		return (NULL);
	FT_INIT(char*, var_path, get_var(&g_shell, "PATH"));
	rep = opendir(path);
	if (rep && !ft_strchr(sentence, ' ') && sentence[0] != '/' && var_path)
		files = store_files_dirs(rep, files, path, str_to_search(sentence));
	else if (rep && path && sentence[ft_strlen(sentence) - 1] != ' ')
		files = store_files_dirs(rep, files, path, str_to_search(sentence));
	else
	{
		closedir(rep);
		rep = opendir(".");
		files = store_files_dirs(rep, files, path, str_to_search(sentence));
	}
	closedir(rep);
	free(var_path);
	return (files);
}

static t_file	*files_list(char **sentence)
{
	FT_INIT(char**, path, NULL);
	FT_INIT(t_file*, files, NULL);
	FT_INIT(t_file*, head, NULL);
	FT_INIT(int, i, 0);
	FT_INIT(char*, home, get_var(&g_shell, "HOME"));
	FT_INIT(char*, pwd, get_var(&g_shell, "PWD"));
	*sentence = default_sentence(sentence);
	path = set_path(sentence, home, pwd);
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

char			*detect_auto_completion(char *sentence)
{
	static int check = 0;

	FT_INIT(t_file*, files, NULL);
	FT_INIT(t_file*, match_files, NULL);
	FT_INIT(char*, new_sentence, NULL);
	FT_INIT(char*, to_search, NULL);
	if (!sentence || !ft_strlen(sentence) || !verif_sentence(sentence))
		return (sentence);
	FT_INIT(char*, copy_sentence, set_copy_sentence(sentence));
	files = files_list(&copy_sentence);
	to_search = str_to_search(copy_sentence);
	if ((match_files = compare_list_sentence(files, to_search)))
		new_sentence = similarity(match_files, to_search);
	if (new_sentence && ft_strlen(new_sentence))
	{
		check = 0;
		return (if_new_sentence(copy_sentence, files, new_sentence));
	}
	if (check != prev_sentence_value(sentence))
		check = prev_sentence_value(sentence);
	display_completion(copy_sentence, match_files);
	ft_strdel(&copy_sentence);
	return (sentence);
}

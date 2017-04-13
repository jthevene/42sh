/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:36:40 by hjacque           #+#    #+#             */
/*   Updated: 2017/04/13 12:28:51 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/history.h"

static char			*get_str_to_replace(char *event)
{
	FT_INIT(char*, tmp, NULL);
	FT_INIT(char*, str_to_replace, NULL);
	FT_INIT(int, i, 1);
	tmp = ft_strdup(ft_strchr(event, '!'));
	while (tmp && tmp[i] && tmp[i] != ' ' && tmp[i] != '!')
		i++;
	i = tmp[1] == '!' ? 2 : i;
	str_to_replace = ft_strsub(tmp, 0, i);
	ft_strdel(&tmp);
	return (str_to_replace);
}

static char			*get_target(char *str_to_replace)
{
	FT_INIT(char*, target, NULL);
	FT_INIT(int, i, 0);
	FT_INIT(int, start, 0);
	FT_INIT(int, end, 0);
	while (str_to_replace && str_to_replace[i] && str_to_replace[i] == '!')
		i++;
	start = i;
	end = ft_strlen(str_to_replace) - 1;
	target = ft_strsub(str_to_replace, start, end);
	return (target);
}

static int			exec_match(char *event, char **str_to_replace,
							char *replace_by)
{
	FT_INIT(char*, tmp, NULL);
	if (!replace_by || (g_shell.current_line
		&& !ft_strcmp(replace_by, g_shell.current_line)))
	{
		ft_putstr_fd("\n42sh: ", 2);
		ft_putstr_fd((*str_to_replace), 2);
		ft_putstr_fd(": event not found", 2);
		ft_strdel(&(*str_to_replace));
		ft_bzero(g_shell.current_line, ft_strlen(g_shell.current_line));
		return (0);
	}
	tmp = ft_str_replace(event, (*str_to_replace), replace_by);
	ft_strdel(&replace_by);
	ft_strdel(&(*str_to_replace));
	ft_strdel(&g_shell.current_line);
	g_shell.current_line = ft_strdup(tmp);
	ft_strdel(&tmp);
	if (g_shell.current_line && ft_strchr(g_shell.current_line, '!'))
		return (history_event(g_shell.current_line));
	ft_putchar('\n');
	ft_putendl(g_shell.current_line);
	return (1);
}

int					history_event(char *event)
{
	FT_INIT(char*, str_to_replace, get_str_to_replace(event));
	FT_INIT(char*, replace_by, NULL);
	FT_INIT(char*, target, get_target(str_to_replace));
	FT_INIT(int, digit, 0);
	FT_INIT(int, alnum, 0);
	FT_INIT(int, mult_ret, ft_strlen(str_to_replace) != ft_strlen(event)
		? 0 : 1);
	while (target && target[digit] &&
		(ft_isdigit(target[digit]) || target[0] == '-'))
		digit++;
	while (target && target[alnum] && ft_isalnum(target[alnum]))
		alnum++;
	if (str_to_replace && !ft_strcmp(str_to_replace, "!!"))
		replace_by = event_n(-1, str_to_replace);
	else if (digit && digit == (int)ft_strlen(target))
		replace_by = event_n(ft_atoi(target), str_to_replace);
	else if (alnum && alnum == (int)ft_strlen(target))
		replace_by = event_str(target, str_to_replace);
	ft_strdel(&target);
	return (exec_match(event, &str_to_replace, replace_by) * mult_ret);
}

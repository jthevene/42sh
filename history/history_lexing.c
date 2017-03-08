/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_lexing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjacque <hjacque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:36:40 by hjacque           #+#    #+#             */
/*   Updated: 2017/03/08 14:46:02 by hjacque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/history.h"

int		invalid_option(void)
{
	FT_INIT(int, i, 0);
	FT_INIT(char, c, 0);
	if (!g_shell.hist_opt.options)
		return (0);
	while (g_shell.hist_opt.options[i])
	{
		c = g_shell.hist_opt.options[i];
		if (ft_isalpha(c) && c != 'a' && c != 'r' && c != 'w' && c != 'p' && \
			c != 's' && c != 'd' && c != 'c')
		{
			ft_putendl_fd("history : invalid option", 2);
			ft_putendl_fd("usage: history [-cdawrps]", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

void	free_hist_opt(void)
{
	if (g_shell.hist_opt.options)
		free(g_shell.hist_opt.options);
	if (g_shell.hist_opt.arg)
		free(g_shell.hist_opt.arg);
	if (g_shell.hist_opt.filename)
		free(g_shell.hist_opt.filename);
}

void	split_line(char *line)
{
	char	**command_tab;
	int		i;

	i = 1;
	command_tab = ft_strsplit(line, ' ');
	i = get_options_str(command_tab);
	get_arg_filename(i, command_tab);
	free_tab(command_tab);
}

void	get_arg_filename(int i, char **array)
{
	FT_INIT(char *, tmp1, NULL);
	FT_INIT(char *, tmp2, NULL);
	if (array[i])
		g_shell.hist_opt.filename = ft_strdup(array[i]);
	while (array[i])
	{
		if (!g_shell.hist_opt.arg)
			g_shell.hist_opt.arg = ft_strdup(array[i]);
		else
		{
			tmp2 = ft_strjoin(g_shell.hist_opt.arg, " ");
			tmp1 = ft_strjoin(tmp2, array[i]);
			free(g_shell.hist_opt.arg);
			g_shell.hist_opt.arg = ft_strdup(tmp1);
			free(tmp1);
			free(tmp2);
		}
		i++;
	}
}

int		get_options_str(char **array)
{
	FT_INIT(int, i, 1);
	FT_INIT(char *, tmp, NULL);
	if (!array[1])
		return (i);
	while (array[i] && array[i][0] == '-')
	{
		if (i == 1)
			g_shell.hist_opt.options = ft_strdup(array[i]);
		else
		{
			tmp = ft_strdup(g_shell.hist_opt.options);
			if (g_shell.hist_opt.options)
				free(g_shell.hist_opt.options);
			g_shell.hist_opt.options = ft_strjoin(tmp, array[i]);
			if (tmp)
				free(tmp);
		}
		i++;
	}
	return (i);
}

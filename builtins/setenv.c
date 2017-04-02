/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvirgile <dvirgile@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:36:40 by hjacque           #+#    #+#             */
/*   Updated: 2017/03/31 15:14:54 by dvirgile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh42.h"

char		*recup_name(char *line)
{
	FT_INIT(int, i, 0);
	FT_INIT(int, start, 0);
	if (!line)
		return (NULL);
	while (line[i] && line[i] != ' ')
		i++;
	if (!line[i])
		return (NULL);
	start = ++i;
	while (line[i])
	{
		if (line[i] == '=' && (start - i) != 0)
			return (ft_strsub(line, start, i - start));
		else if (line[i] == '=' && (start - i) == 0)
			return (NULL);
		i++;
	}
	return (NULL);
}

char		*recup_value(char *line)
{
	FT_INIT(int, i, 0);
	if (!line)
		return (NULL);
	while (line[i])
	{
		if (i > 1 && line[i - 1] == '=')
			return (ft_strsub(line, i, ft_strlen(line) - i));
		i++;
	}
	return (NULL);
}

int			check_setenv(char **name, char **value, int env)
{
	if (!(*name))
	{
		free_triple_str(&(*name), &(*value), NULL);
		ft_putendl_fd("42sh: setenv: Invalid argument", 2);
		return (0);
	}
	else if ((*value) && ft_strchr((*value), '='))
	{
		ft_putendl_fd("42sh: setenv: Invalid argument", 2);
		free((*name) ? (*name) : NULL);
		free((*value) ? (*value) : NULL);
		return (0);
	}
	else if (((env == DEFAULT && !g_shell.env)
		|| (env == TMP && !g_shell.tmp_env)) && (*name))
	{
		if (env == DEFAULT)
			g_shell.env = new_var((*name), (*value));
		else
			g_shell.tmp_env = new_var((*name), (*value));
		free((*name));
		free((*value) ? (*value) : NULL);
		return (0);
	}
	return (1);
}

int			ft_setenv(char *line, int env)
{
	FT_INIT(t_var *, tmp, env == DEFAULT ? g_shell.env : g_shell.tmp_env);
	FT_INIT(char *, name, recup_name(line));
	FT_INIT(char *, value, recup_value(line));
	if (!check_setenv(&name, &value, env))
		return (0);
	while (tmp)
	{
		if (!ft_strcmp(name, tmp->name))
		{
			free(name);
			free(tmp->value);
			tmp->value = value ? value : ft_strdup("");
			return (1);
		}
		if (!tmp->next)
		{
			FT_INIT(t_var *, new, new_var(name, value));
			free(name);
			free(value ? value : NULL);
			tmp->next = new;
			return (1);
		}
		tmp = tmp->next;
	}
	return (1);
}

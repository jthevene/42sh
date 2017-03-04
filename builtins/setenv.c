/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinho <apinho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 18:13:29 by apinho            #+#    #+#             */
/*   Updated: 2017/02/24 18:36:50 by apinho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

char		*recup_name(char *line)
{
	FT_INIT(int, i, 0);
	FT_INIT(int, start, 0);
	while (line[i] && line[i] != ' ')
		i++;
	if (!line[i])
		return (NULL);
	start = ++i;
	while (line[i])
	{
		if (line[i] == '=')
			return (ft_strsub(line, start, i - start));
		i++;
	}
	return (NULL);
}

char		*recup_value(char *line)
{
	FT_INIT(int, i, 0);
	while (line[i])
	{
		if (i > 1 && line[i - 1] == '=')
			return (ft_strsub(line, i, ft_strlen(line) - i));
		i++;
	}
	return (NULL);
}

int			check_setenv(char **name, char **value)
{
	if (!(*name))
	{
		free((*name) ? (*name) : NULL);
		free((*value) ? (*value) : NULL);
		return (0);
	}
	else if (ft_strchr((*value), '='))
	{
		free((*name) ? (*name) : NULL);
		free((*value) ? (*value) : NULL);
		return (0);
	}
	else if (!g_shell.env && (*name))
	{
		g_shell.env = new_var((*name), (*value));
		free((*name));
		free((*value) ? (*value) : NULL);
		return (0);
	}
	return (1);
}

int			ft_setenv(char *line)
{
	FT_INIT(t_var *, tmp, g_shell.env);
	FT_INIT(char *, name, recup_name(line));
	FT_INIT(char *, value, recup_value(line));
	if (!check_setenv(&name, &value))
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

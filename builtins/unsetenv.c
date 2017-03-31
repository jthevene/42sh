/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjacque <hjacque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:36:40 by hjacque           #+#    #+#             */
/*   Updated: 2017/03/08 14:46:43 by hjacque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh42.h"

void		free_node(t_var **to_free)
{
	free((*to_free)->name);
	free((*to_free)->value);
	free((*to_free));
	(*to_free) = NULL;
}

char		*unsetenv_get_name(char *line)
{
	FT_INIT(int, i, 0);
	FT_INIT(int, j, 0);
	FT_INIT(int, len, 0);
	while (line[i] && line[i] != ' ')
		i++;
	j = ++i;
	while (line[i] && line[i] != ' ')
	{
		i++;
		len++;
	}
	return (ft_strsub(line, j, len));
}

int			ft_unsetenv_suite(t_var **tmp, t_var **tmp_prev,
							t_var **tmp_next, t_var **tmp_free)
{
	if (!(*tmp_prev) && !(*tmp_next))
	{
		free_node(&(*tmp_free));
		g_shell.env = NULL;
		return (1);
	}
	if (!(*tmp_prev))
	{
		free_node(&(*tmp_free));
		g_shell.env = (*tmp);
		return (1);
	}
	else if (!(*tmp_next))
	{
		free_node(&(*tmp_free));
		(*tmp_prev)->next = NULL;
		return (1);
	}
	else
	{
		free_node(&(*tmp_free));
		(*tmp_prev)->next = (*tmp_next);
		return (1);
	}
	return (0);
}

static int	free_name_unsetenv(int val_to_return, char **name)
{
	if ((*name))
		free((*name));
	return (val_to_return);
}

int			ft_unsetenv(char *line)
{
	if (!g_shell.env)
		return (0);
	FT_INIT(t_var *, tmp, g_shell.env);
	FT_INIT(t_var *, tmp_free, NULL);
	FT_INIT(t_var *, tmp_prev, NULL);
	FT_INIT(t_var *, tmp_next, NULL);
	FT_INIT(char *, name, unsetenv_get_name(line));
	if (!name)
		return (0);
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
		{
			tmp_free = tmp;
			tmp_next = tmp->next;
			tmp = tmp->next ? tmp->next : tmp;
			if (ft_unsetenv_suite(&tmp, &tmp_prev, &tmp_next, &tmp_free) == 1)
				return (free_name_unsetenv(1, &name));
		}
		tmp_prev = tmp;
		tmp = tmp->next;
	}
	return (free_name_unsetenv(0, &name));
}

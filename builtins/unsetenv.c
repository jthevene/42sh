/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 15:37:30 by sgaudin           #+#    #+#             */
/*   Updated: 2017/02/13 12:38:51 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

void		free_node(t_var **to_free)
{
	free((*to_free)->name);
	free((*to_free)->value);
	free((*to_free));
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
								t_var **tmp_free, char **name)
{
	if (!(*tmp_prev))
	{
		free_node(&(*tmp_free));
		g_shell.env = (*tmp);
		free((*name));
		return (1);
	}
	else
	{
		free_node(&(*tmp_free));
		(*tmp_prev)->next = NULL;
		free((*name));
		return (1);
	}
	return (0);
}

int			ft_unsetenv(char *line)
{
	FT_INIT(t_var *, tmp, g_shell.env);
	FT_INIT(t_var *, tmp_free, NULL);
	FT_INIT(t_var *, tmp_prev, NULL);
	FT_INIT(char *, name, unsetenv_get_name(line));
	if (!name)
		return (0);
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
		{
			tmp_free = tmp;
			tmp = tmp->next;
			if (ft_unsetenv_suite(&tmp, &tmp_prev, &tmp_free, &name) == 1)
				return (1);
		}
		tmp_prev = tmp;
		tmp = tmp->next;
	}
	free(name);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cbracket_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 15:37:23 by sgaudin           #+#    #+#             */
/*   Updated: 2016/11/21 15:37:24 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/globing.h"

int		is_expansion(char *line, int i)
{
	while (line[i])
	{
		if (line[i] == '{')
		{
			if (!is_expansion(line, i + 1))
				return (0);
			i += next_bracket(line, '{', i);
		}
		if (line[i] == '.' && line[i + 1] == '.')
			return (1);
		i++;
	}
	return (1);
}

int		valid_expansion(char *line)
{
	FT_INIT(int, i, 0);
	while (line[i])
	{
		if (line[i] == '.' && line[i + 1] == '.')
		{
			if (!(line[i - 1] && line[i - 2] && line[i - 2] == '{'))
				return (0);
			if (!(line[i + 2] && line[i + 3] && line[i + 3] == '}'))
				return (0);
			return (1);
		}
		i++;
	}
	return (1);
}

int		cbracket_errors(char *line, t_glob *glob)
{
	FT_INIT(char *, tmp, NULL);
	if (ft_strchr(line, ' '))
	{
		tmp = ft_strjoin("42sh: Spaces are forbidden in expression: ", glob->command);
		ft_putendl_fd(tmp, 2);
		free(tmp);
		return (0);
	}
	else if (!check_commas(line, 0))
	{
		tmp = ft_strjoin("42sh: Bad pattern in expression: ", glob->command);
		ft_putendl_fd(tmp, 2);
		ft_putendl_fd("Pattern should be of type: \"{,*.c}\", or \"{*.c,*.h}\"", 2);
		free(tmp);
		return (0);
	}
	return (1);
}

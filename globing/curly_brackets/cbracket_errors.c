/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cbracket_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 12:00:14 by sgaudin           #+#    #+#             */
/*   Updated: 2017/04/10 14:58:12 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/globing.h"

int		is_expansion(char *line)
{
	FT_INIT(int, i, 0);
	while (i < (int)ft_strlen(line) && line[i])
	{
		if (line[i] == '.')
		{
			if (line[i + 1] && line[i + 1] == '.')
			{
				if (line[i + 2] && ft_isalnum(line[i + 2]))
					return (1);
				else
					return (0);
			}
		}
		i++;
	}
	return (0);
}

int		cbracket_errors(char *line, t_glob *glob)
{
	FT_INIT(char *, tmp, NULL);
	FT_INIT(int, i, 0);
	while (line[i] != '{')
		i++;
	if (ft_strchr(line, ' '))
	{
		tmp = ft_strjoin("42sh: Spaces are forbidden in expression: "
			, glob->command);
		ft_putendl_fd(tmp, 2);
		free(tmp);
		free(line);
		return (0);
	}
	else if (!check_commas(line, i) && !(is_expansion(line)))
	{
		tmp = ft_strjoin("42sh: Bad pattern in expression: ", glob->command);
		ft_putendl_fd(tmp, 2);
		ft_putendl_fd("Pattern should be of type: \"{,*.c}\","
			" \"{*.c,*.h}\" or \"{1..9}\"", 2);
		free(tmp);
		free(line);
		return (0);
	}
	return (1);
}

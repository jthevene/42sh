/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cbracket_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinho <apinho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 18:13:29 by apinho            #+#    #+#             */
/*   Updated: 2017/02/24 18:35:48 by apinho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/globing.h"

int		is_expansion(char *line)
{
	FT_INIT(int, i, 0);
	while (line[i])
	{
		if (line[i] == '.' && line[i + 1] == '.')
			return (1);
		i++;
	}
	return (0);
}

int		cbracket_errors(char *line, t_glob *glob)
{
	FT_INIT(char *, tmp, NULL);
	if (ft_strchr(line, ' '))
	{
		tmp = ft_strjoin("21sh: Spaces are forbidden in expression: "
			, glob->command);
		ft_putendl_fd(tmp, 2);
		free(tmp);
		free(line);
		return (0);
	}
	else if (!check_commas(line, 0) && !(is_expansion(line)))
	{
		tmp = ft_strjoin("21sh: Bad pattern in expression: ", glob->command);
		ft_putendl_fd(tmp, 2);
		ft_putendl_fd("Pattern should be of type: \"{,*.c}\","
			" \"{*.c,*.h}\" or \"{1..9}\"", 2);
		free(tmp);
		free(line);
		return (0);
	}
	return (1);
}

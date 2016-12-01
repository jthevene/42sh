/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cbracket_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 15:12:28 by sgaudin           #+#    #+#             */
/*   Updated: 2016/11/25 15:12:29 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/globing.h"

int					last_bracket(char *str, int c)
{
	FT_INIT(int, i, 0);
	FT_INIT(int, ret, 0);
	FT_INIT(int, count, c);
	while (str[i])
		i++;
	--i;
	ret = i;
	while (str[i])
	{
		if (str[i] == '{')
		{
			count--;
			if (!count)
				break ;
		}
		i--;
		ret--;
	}
	return (ret);
}

char				*next_expr(char *str, int i)
{
	FT_INIT(int, ret, 0);
	FT_INIT(int, j, 0);
	while (str[i] != ' ')
		i--;
	i++;
	j = i;
	while (str[i])
	{
		if (str[i] == ' ')
			break ;
		i++;
		ret++;
	}
	return (ft_strsub(str, j, ret));
}

void				free_double_tab(char ***tabl)
{
	FT_INIT(int, i, 0);
	while ((*tabl)[i])
	{
		if ((*tabl)[i])
			free((*tabl)[i]);
		i++;
	}
	free((*tabl));
}

int					detect_double_bracket(char *str)
{
	FT_INIT(int, i, 0);
	while (str[i])
	{
		if (str[i] == '{' && str[i + 1] == '{')
			return (1);
		i++;
	}
	return (0);
}

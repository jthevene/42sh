/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_expr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 14:20:39 by sgaudin           #+#    #+#             */
/*   Updated: 2016/11/14 14:20:41 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/globing.h"

char 		*separate_chars_debut(char *str, int pos)
{
	FT_INIT(char *, ret, ft_strnew(mixed_expr_get_len(str, pos)));
	FT_INIT(int, i, 1);
	FT_INIT(int, j, -1);
	ret[++j] = '[';
	while (str[i] && (str[i] != '[' && str[i + 1] != ':'))
	{
		ret[++j] = str[i];
		i++;
	}
	while (str[i])
	{
		if (str[i + 1] == ':' && str[i + 2] == ']')
		{
			i += 3;
			break ;
		}
		i++;
	}
	if (str[i] && str[i] != ']')
	{
		while (str[i])
		{
			ret[++j] = str[i];
			i++;
		}
	}
	return (ret);
}

char		*separate_chars_fin(char *str, int pos)
{
	FT_INIT(char *, ret, ft_strnew(mixed_expr_get_len(str, pos)));
	FT_INIT(int, i, 0);
	FT_INIT(int, j, -1);
	ret[++j] = str[i++];
	while (str[i])
	{
		if (str[i] == ']' && str[i - 1] == ':')
			break ;
		i++;
	}
	while (str[i])
		ret[++j] = str[++i];
	ret[++j] = '\0';
	return (ret);
}
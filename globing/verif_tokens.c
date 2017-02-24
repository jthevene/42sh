/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinho <apinho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 18:13:29 by apinho            #+#    #+#             */
/*   Updated: 2017/02/24 18:35:55 by apinho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/globing.h"

int					ft_strchr_quotes(char *s, int c)
{
	FT_INIT(int, i, 0);
	FT_INIT(int, quote, 0);
	FT_INIT(int, found, 0);
	while (s[i] && i < (int)ft_strlen(s))
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			quote = s[i++];
			while (s[i] && s[i] != quote)
			{
				if ((c == '{' || c == '}') && s[i] == ',')
					return (0);
				i++;
			}
		}
		if (s[i] == c)
			found++;
		i++;
	}
	return (found);
}

int					ft_strchr_bslash(char *s, int c)
{
	FT_INIT(int, i, 0);
	FT_INIT(int, found, 0);
	while (s[i] && i < (int)ft_strlen(s))
	{
		if (s[i] == '\\' && s[i + 1] == c)
			return (0);
		else if ((c == '{' || c == '}') && s[i] == '\\' && s[i + 1] == ',')
			return (0);
		if (s[i] == '\\')
			i++;
		if (s[i] == (char)c)
			found++;
		i++;
	}
	if (ft_strchr(s, '\'') || ft_strchr(s, '"'))
		return (ft_strchr_quotes(s, c));
	return (found);
}

int					verif_tokens(char **str)
{
	FT_INIT(int, nb, 0);
	if (ft_strchr_bslash((*str), '[') && !ft_strchr_bslash((*str), ']'))
		return (0);
	else if (!ft_strchr_bslash((*str), '[') && ft_strchr_bslash((*str), ']'))
		return (0);
	else if (!count_brackets((*str), '['))
		return (0);
	else if (ft_strchr_bslash((*str), '[') && ft_strchr_bslash((*str), ']'))
		nb++;
	if (ft_strchr_bslash((*str), '{') && !ft_strchr_bslash((*str), '}'))
		return (0);
	else if (ft_strchr_bslash((*str), '{') && !ft_strchr_bslash((*str), '}'))
		return (0);
	else if (!count_brackets((*str), '{'))
		return (0);
	else if (ft_strchr_bslash((*str), '{') && ft_strchr_bslash((*str), '}'))
		nb++;
	if ((ft_strchr((*str), '*') && !ft_strchr_bslash((*str), '*'))
		|| (ft_strchr((*str), '?') && !ft_strchr_bslash((*str), '?')))
		return (0);
	else if (ft_strchr_bslash((*str), '*') || ft_strchr_bslash((*str), '?'))
		nb++;
	return (!nb ? 0 : 1);
}

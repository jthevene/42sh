/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 11:51:18 by sgaudin           #+#    #+#             */
/*   Updated: 2017/01/27 11:51:19 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/globing.h"

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
	return (found);
}

int					verif_tokens(char *str)
{
	FT_INIT(int, nb, 0);
	if (ft_strchr_bslash(str, '[') && !ft_strchr_bslash(str, ']'))
		return (0);
//	else if (!count_brackets(str, '['))
//		return (0); 
	else if (ft_strchr_bslash(str, '[') && ft_strchr_bslash(str, ']'))
		nb++;
	if (ft_strchr_bslash(str, '{') && !ft_strchr_bslash(str, '}'))
		return (0);
	else if (!count_brackets(str, '{'))
		return (0);
	else if (ft_strchr_bslash(str, '{') && ft_strchr_bslash(str, '}'))
		nb++;
	if (ft_strchr_bslash(str, '*') || ft_strchr_bslash(str, '?'))
		nb++;
	if (!nb)
		return (0);
	return (1);
}
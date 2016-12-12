/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 18:23:31 by sgaudin           #+#    #+#             */
/*   Updated: 2016/12/12 18:23:31 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/globing.h"

int			get_len_token(char *str)
{
	FT_INIT(int, i, 0);
	FT_INIT(int, len, 0);
	while (str[i])
	{
		if (str[i] != '*' && str[i] != '[')
			len++;
		if (str[i] == '[')
		{
			len++;
			i += next_bracket(str, '[', i);
		}
		i++;
	}
	return (len);
}

char		*get_token(char *str)
{
	FT_INIT(int, i, 0);
	FT_INIT(int, i2, 0);
	FT_INIT(int, j, 0);
	while (str[i] && !ft_strchr("*[?", str[i]))
		i++;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '/')
		i--;
	if (!str[i])
		return (ft_strdup(str));
	i2 = ++i;
	while (str[i] && str[i] != '/')
	{
		i++;
		j++;
	}
	return (ft_strsub(str, i2, j));
}

int			ft_istrchr(const char *s, int c, int i)
{
	while (s[i] && s[i] != (char)c)
		i++;
	if (s[i] == (char)c)
		return (1);
	return (0);
}
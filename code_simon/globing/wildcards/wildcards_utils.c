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

int		get_len_token(char *str)
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

char	*get_token(char *str)
{
	FT_INIT(int, i, 0);
	FT_INIT(int, i2, 0);
	FT_INIT(int, j, 0);
	while (str[i] && !ft_strchr("*[?", str[i]))
		i++;
	if (!str[i])
		return (NULL);
	while (i >= 0 && str[i] && str[i] != '/')
		i--;
	i2 = ++i;
	while (str[i] && str[i] != '/')
	{
		i++;
		j++;
	}
	return (ft_strsub(str, i2, j));
}

char	*get_next_star(char *str, int i)
{
	FT_INIT(int, start, i);
	FT_INIT(int, len, 0);
	while (str[i] && str[i] != '*')
	{
		len++;
		i++;
	}
	if (!len)
		return (NULL);
	return (ft_strsub(str, start, len));
}

char	*ft_istrchr(const char *s, int c, int i)
{
	while (s[i] && s[i] != (char)c)
		i++;
	if (s[i] == (char)c)
		return ((char*)&s[i]);
	return (NULL);
}

int		ft_istrstr(char *s1, char *s2, int i, t_glob *g)
{
	FT_INIT(int, j, 0);
	FT_INIT(int, ret, 0);
	FT_INIT(int, taille, ft_strlen(s2));
	if (!taille || !g)
		return (0);
	i = s2[j] == '?' ? i + 1 : i;
	while (s1[i])
	{
		j = s2[j] == '?' ? j + 1 : j;
		while ((ret = i + j) >= 0 && s1[i + j] && s2[j] && (s1[i + j] == s2[j]
			|| s2[j] == '[' || s2[j] == '?'))
		{
			if (s2[j] == '[')
				ret = ft_check_bracket(s1, i + j
				, j + next_bracket(s2, '[', j) == taille - 1 ? FALSE : TRUE, g);
			j += s2[j] == '[' ? next_bracket(s2, '[', j) : 0;
			if (j == taille - 1)
				return (ret);
			j++;
			ret++;
		}
		j = 0;
		i++;
	}
	return (0);
}

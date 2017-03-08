/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjacque <hjacque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 18:13:29 by hjacque           #+#    #+#             */
/*   Updated: 2017/03/08 14:51:23 by hjacque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static size_t		ft_tab_len(const char *s, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			j++;
		while (s[i] && s[i] != c)
			i++;
		while (s[i] && s[i] == c)
			i++;
	}
	return (j);
}

static size_t		ft_wi(size_t index, const char *s, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			j++;
		if (j == index + 1)
			return (i);
		while (s[i] && s[i] != c)
			i++;
	}
	return (0);
}

static size_t		ft_wl(size_t index, const char *s, char c)
{
	size_t	i;
	size_t	ret;

	i = ft_wi(index, s, c);
	ret = 0;
	while (s[i] && s[i] != c)
	{
		i++;
		ret++;
	}
	return (ret);
}

char				**ft_strsplit(char const *s, char c)
{
	FT_INIT(size_t, j, 0);
	FT_INIT(size_t, i, 0);
	FT_INIT(size_t, l, 0);
	FT_INIT(char**, ret, NULL);
	if (s)
		ret = (char **)ft_memalloc(sizeof(char *) * (ft_tab_len(s, c) + 1));
	if (ret)
	{
		j = 0;
		while (j < ft_tab_len(s, c))
		{
			ret[j] = (char *)ft_memalloc(ft_wl(j, s, c) + 1);
			if (ret[j])
			{
				i = ft_wi(j, s, c);
				l = 0;
				while (i - ft_wi(j, s, c) < ft_wl(j, s, c))
					ret[j][l++] = s[i++];
				ret[j][l] = 0;
			}
			j++;
		}
		ret[j] = NULL;
	}
	return (ret);
}

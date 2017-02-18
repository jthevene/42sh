/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 17:32:24 by sgaudin           #+#    #+#             */
/*   Updated: 2016/02/03 10:33:03 by sgaudin          ###   ########.fr       */
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
	char	**ret;
	size_t	i;
	size_t	j;
	size_t	l;

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

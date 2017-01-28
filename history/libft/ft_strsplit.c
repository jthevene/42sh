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

static int	ft_countwords(char const *s, char c)
{
	int i;
	int words;

	i = 0;
	words = 0;
	if (s[i] != c)
		words++;
	while (s[i] == c && s[i] != '\0')
		i++;
	while (s[i] != '\0')
	{
		if (s[i - 1] == c && s[i] != c)
			words++;
		i++;
	}
	return (words);
}

static int	ft_length(char const *s, char c)
{
	int length;
	int i;

	length = 0;
	i = 0;
	while (s[i] != '\0' && s[i] != c)
	{
		length++;
		i++;
	}
	if (length == 0)
		length++;
	return (length);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**tab;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	tab = (char**)malloc(sizeof(char *) * (ft_countwords(s, c) + 1));
	if (tab == NULL)
		return (NULL);
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			tab[i] = ft_strsub(s, 0, ft_length(s, c));
			if (tab[i] == NULL)
				return (NULL);
			s = s + ft_length(s, c);
			i++;
		}
	}
	tab[i] = NULL;
	return (tab);
}

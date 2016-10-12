/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthevene <jthevene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/17 16:54:30 by jthevene          #+#    #+#             */
/*   Updated: 2015/03/07 18:09:06 by jthevene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_nb_strings(const char *s, char c)
{
	static int		i;
	static int		nb_strings;

	i = 0;
	nb_strings = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		while (s[i] != c && s[i] != '\0')
			i++;
		if (s[i] != '\0' || s[i - 1] != c)
			nb_strings++;
	}
	return (nb_strings);
}

char	**ft_supersplit(char const *s, char c, char ***res)
{
	static int		i;
	static int		j;
	static int		k;

	i = 0;
	k = 0;
	j = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != c && s[i] != '\0')
		{
			j = i;
			while (s[i] != c && s[i] != '\0')
				i++;
			if (s[i] != '\0' || s[i - 1] != c)
			{
				res[0][k] = ft_strsub(s, j, i - j);
				k++;
			}
		}
	}
	res[0][k] = NULL;
	return (*res);
}

char	**ft_strsplit(char const *s, char c)
{
	char	**res;
	int		nb_strings;

	nb_strings = 0;
	if (s == NULL)
		return (NULL);
	nb_strings = ft_nb_strings(s, c);
	res = (char **)malloc(sizeof(char *) * (nb_strings + 1));
	if (res == NULL)
		return (NULL);
	if (nb_strings == 0)
	{
		res[0] = NULL;
		return (res);
	}
	return (ft_supersplit(s, c, &res));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthevene <jthevene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/12 16:53:45 by jthevene          #+#    #+#             */
/*   Updated: 2014/11/17 19:04:57 by jthevene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		start(const char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ' || str[i] == ',' || str[i] == '\n' || str[i] == '\t')
	{
		i++;
		if (str[i] == '\0')
			return (-1);
	}
	return (i);
}

static int		end(const char *str)
{
	int i;

	i = ft_strlen(str) - 1;
	while (str[i] == ' ' || str[i] == ',' || str[i] == '\n' || str[i] == '\t')
	{
		i--;
	}
	return (i);
}

char			*ft_strtrim(const char *s)
{
	int		i;
	int		j;
	char	*dest;

	if (s == NULL)
		return (NULL);
	i = 0;
	j = start(s);
	if (i == -1)
		return ("");
	dest = (char *)malloc(sizeof(char) * (end(s) - start(s) + 1));
	if (dest == NULL)
		return (NULL);
	while (j <= end(s))
	{
		dest[i] = s[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 15:55:27 by sgaudin           #+#    #+#             */
/*   Updated: 2016/02/03 10:34:12 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static int	count_spaces(char const *s)
{
	int		i;
	size_t	spaces;

	i = 0;
	spaces = 0;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
	{
		i++;
		spaces++;
	}
	if (spaces == ft_strlen(s))
		return (spaces);
	while (s[i] != '\0')
		i++;
	i--;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
	{
		i--;
		spaces++;
	}
	return (spaces);
}

char		*ft_strtrim(char const *s)
{
	int				spaces;
	char			*new_string;
	unsigned int	i;
	unsigned int	j;

	if (!s)
		return (NULL);
	spaces = count_spaces(s);
	i = 0;
	j = 0;
	new_string = (char*)malloc(sizeof(new_string) * (ft_strlen(s) - spaces));
	if (new_string == NULL)
		return (NULL);
	if (spaces == 0)
		new_string = ft_strcpy(new_string, s);
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		i++;
	while (j < (ft_strlen(s) - spaces))
		new_string[j++] = s[i++];
	new_string[j] = '\0';
	return (new_string);
}

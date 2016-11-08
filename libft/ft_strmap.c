/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 14:24:55 by sgaudin           #+#    #+#             */
/*   Updated: 2016/02/03 10:31:10 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*string;
	size_t	size;
	int		i;

	i = 0;
	if (!s || !f)
		return (NULL);
	size = ft_strlen(s);
	string = (char*)malloc(sizeof(string) * size + 1);
	if (string == NULL)
		return (NULL);
	while (s[i])
	{
		string[i] = f(s[i]);
		i++;
	}
	string[i] = '\0';
	return (string);
}

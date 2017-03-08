/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjacque <hjacque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 18:13:29 by hjacque           #+#    #+#             */
/*   Updated: 2017/03/08 14:51:16 by hjacque          ###   ########.fr       */
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
	string = (char*)malloc(sizeof(string) * (size + 1));
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

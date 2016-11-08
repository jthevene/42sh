/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 15:20:05 by sgaudin           #+#    #+#             */
/*   Updated: 2016/02/03 10:31:22 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*string;
	int				size;
	unsigned int	i;

	i = 0;
	if (s)
	{
		size = ft_strlen(s);
		if (size > 0)
			string = (char *)malloc(sizeof(string) * size + 1);
		if (f)
		{
			while (s[i])
			{
				string[i] = f(i, (char)s[i]);
				i++;
			}
			string[i] = '\0';
			return (string);
		}
	}
	return (NULL);
}

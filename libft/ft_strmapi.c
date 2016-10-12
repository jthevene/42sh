/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthevene <jthevene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/11 17:27:27 by jthevene          #+#    #+#             */
/*   Updated: 2014/11/11 19:03:55 by jthevene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	size_t	i;

	i = 0;
	if (s && f)
	{
		str = (char *)malloc(sizeof(*s) * (ft_strlen(s) + 1));
		if (!str)
			return (NULL);
		while (s[i] != '\0')
		{
			str[i] = f(i, (char)s[i]);
			i++;
		}
		str[i] = '\0';
		return (str);
	}
	return (NULL);
}

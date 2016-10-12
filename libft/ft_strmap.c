/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthevene <jthevene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/11 16:32:46 by jthevene          #+#    #+#             */
/*   Updated: 2014/11/11 18:52:20 by jthevene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
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
			str[i] = f((char)s[i]);
			i++;
		}
		str[i] = '\0';
		return (str);
	}
	return (NULL);
}

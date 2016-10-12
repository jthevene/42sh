/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthevene <jthevene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 16:23:27 by jthevene          #+#    #+#             */
/*   Updated: 2014/11/10 16:30:04 by jthevene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	c2;

	c2 = c;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c2)
			return ((char*)&s[i]);
		i++;
	}
	if (s[i] == c2)
		return ((char*)&s[i]);
	return (0);
}

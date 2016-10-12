/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthevene <jthevene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 17:03:15 by jthevene          #+#    #+#             */
/*   Updated: 2014/11/10 15:01:47 by jthevene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *src, const char *str)
{
	size_t		i;

	i = ft_strlen(str);
	if (!*str)
		return ((char *)src);
	while (*src)
	{
		if (!ft_strncmp(src, str, i))
			return ((char *)src);
		src++;
	}
	return (0);
}

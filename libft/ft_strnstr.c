/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthevene <jthevene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/08 14:28:58 by jthevene          #+#    #+#             */
/*   Updated: 2014/11/10 15:23:08 by jthevene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *src, const char *str, size_t n)
{
	size_t		i;

	i = ft_strlen(str);
	if (!*str)
		return ((char *)src);
	while (*src && n >= i)
	{
		if (!ft_strncmp(src, str, i))
			return ((char *)src);
		n--;
		src++;
	}
	return (0);
}

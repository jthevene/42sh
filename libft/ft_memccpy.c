/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthevene <jthevene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 17:07:05 by jthevene          #+#    #+#             */
/*   Updated: 2014/11/26 17:55:12 by jthevene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	char		*d;
	const char	*s;

	d = dest;
	s = src;
	while (n > 0)
	{
		*d = *s;
		if (*s == c)
			return (d + 1);
		d++;
		s++;
		n--;
	}
	return (NULL);
}

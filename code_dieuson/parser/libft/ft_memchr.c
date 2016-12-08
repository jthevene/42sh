/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinho <apinho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/13 01:59:03 by apinho            #+#    #+#             */
/*   Updated: 2016/09/20 15:34:12 by apinho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*scp;
	size_t			x;

	x = 0;
	scp = (unsigned char *)s;
	while (x < n)
	{
		if (*scp == (unsigned char)c)
			return ((void *)scp);
		scp++;
		x++;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memchr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 17:15:12 by sgaudin           #+#    #+#             */
/*   Updated: 2016/02/03 10:24:42 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	tmp;
	size_t			i;

	i = 0;
	tmp = (unsigned char)c;
	str = (unsigned char *)s;
	if (str)
	{
		while (n--)
		{
			if (str[i] == tmp)
				return ((void*)&str[i]);
			i++;
		}
	}
	return (NULL);
}

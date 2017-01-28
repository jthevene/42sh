/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 15:19:48 by sgaudin           #+#    #+#             */
/*   Updated: 2016/02/03 10:25:35 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*b2;
	unsigned int	i;

	b2 = b;
	i = 0;
	if (len > 0)
	{
		while (i != len)
		{
			b2[i] = (unsigned char)c;
			i++;
		}
	}
	return (b);
}

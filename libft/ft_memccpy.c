/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinho <apinho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 18:13:29 by apinho            #+#    #+#             */
/*   Updated: 2017/02/24 18:34:16 by apinho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	char			*temp_src;
	char			*temp_dst;
	unsigned int	i;

	temp_src = (char*)src;
	temp_dst = dst;
	i = 0;
	if (n > 0)
	{
		while (i < n)
		{
			temp_dst[i] = temp_src[i];
			if (temp_src[i] == (char)c)
				return (dst + (i + 1));
			i++;
		}
	}
	return (NULL);
}

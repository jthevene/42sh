/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthevene <jthevene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/13 16:38:22 by jthevene          #+#    #+#             */
/*   Updated: 2014/11/18 17:04:54 by jthevene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_str_nbr(int nbr, char *dst)
{
	if (nbr >= 0)
	{
		if (nbr >= 10)
		{
			ft_str_nbr(nbr / 10, dst);
			ft_str_nbr(nbr % 10, dst);
		}
		else
			dst[ft_strlen(dst)] = nbr + '0';
	}
	else
	{
		dst[0] = '-';
		ft_str_nbr(-nbr, dst);
	}
}

char			*ft_itoa(int nbr)
{
	char	*dst;

	dst = malloc(sizeof(char) * 11);
	if (!dst)
		return (NULL);
	ft_bzero(dst, 13);
	if (nbr == -2147483648)
	{
		ft_str_nbr(nbr + 1, dst);
		dst[10] = '8';
	}
	else
		ft_str_nbr(nbr, dst);
	return (dst);
}

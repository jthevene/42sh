/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinho <apinho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 13:04:06 by apinho            #+#    #+#             */
/*   Updated: 2016/09/20 15:33:50 by apinho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*ft_fillstr2(long int nb, char *str, int i)
{
	int			temp;
	int			size;

	temp = nb;
	size = 1;
	while (temp / 10 > 0)
	{
		size = size * 10;
		temp = temp / 10;
	}
	while (size > 0)
	{
		temp = 0;
		temp = nb / size;
		nb = nb % size;
		size = size / 10;
		str[i] = '0' + temp;
		i++;
	}
	str[i] = '\0';
	return (str);
}

char			*ft_ltoa(long int nb)
{
	int			i;
	char		*str;

	str = (char *)malloc(13);
	i = 0;
	if (nb < 0)
	{
		str[i] = '-';
		nb = -nb;
		i++;
	}
	str = ft_fillstr2(nb, str, i);
	return (str);
}

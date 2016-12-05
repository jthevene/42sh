/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinho <apinho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/13 01:54:44 by apinho            #+#    #+#             */
/*   Updated: 2016/09/20 15:33:14 by apinho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_except(char *str)
{
	str[0] = '-';
	str[1] = '2';
	str[2] = '1';
	str[3] = '4';
	str[4] = '7';
	str[5] = '4';
	str[6] = '8';
	str[7] = '3';
	str[8] = '6';
	str[9] = '4';
	str[10] = '8';
	str[11] = '\0';
	return (str);
}

static char		*ft_fillstr(int nb, char *str, int i)
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

char			*ft_itoa(int nb)
{
	int			i;
	char		*str;

	str = (char *)malloc(13);
	i = 0;
	if (nb == -2147483648)
		return (ft_except(str));
	if (nb < 0)
	{
		str[i] = '-';
		nb = -nb;
		i++;
	}
	str = ft_fillstr(nb, str, i);
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 14:52:35 by sgaudin           #+#    #+#             */
/*   Updated: 2016/02/03 10:22:34 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static int	ft_sign(int n)
{
	if (n < 0)
		return (1);
	return (0);
}

static int	ft_size(int n)
{
	int size;

	size = 0;
	if (!n)
		return (0);
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char		*ft_itoa(int n)
{
	char	*str;
	int		i;
	int		sign;

	sign = ft_sign(n);
	str = (char*)malloc(sizeof(str) * (ft_size(n) + sign + 1));
	if (!str)
		return (NULL);
	if (sign == 1)
		n = -n;
	i = ft_size(n) + sign;
	str[i] = '\0';
	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	while (n != 0)
	{
		str[--i] = ((n % 10) + '0');
		n /= 10;
	}
	if (sign == 1)
		str[--i] = '-';
	return (str);
}

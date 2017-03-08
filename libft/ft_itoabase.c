/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoabase.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjacque <hjacque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 18:13:29 by hjacque           #+#    #+#             */
/*   Updated: 2017/03/08 14:50:18 by hjacque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static long		size(long n, int base)
{
	int size;

	size = 0;
	if (!n)
		return (0);
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= base;
		size++;
	}
	return (size);
}

char			*ft_itoa_base(int n, int base)
{
	char	*str;
	int		i;

	if (base == 10)
		return (ft_itoa(n));
	if (base < 2 || base > 16 || (base != 10 && n < 0))
		return (NULL);
	str = (char *)malloc(sizeof(char) * (size(n, base) + 1));
	if (!str)
		return (NULL);
	i = size(n, base);
	str[i] = '\0';
	if (n == 0)
		return (ft_strdup("0"));
	while (n != 0)
	{
		if (base > 10 && (n % base >= 10))
			str[--i] = (n % base) - 10 + 'A';
		else
			str[--i] = (n % base) + '0';
		n /= base;
	}
	return (str);
}

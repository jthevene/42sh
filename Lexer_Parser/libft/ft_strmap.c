/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinho <apinho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/13 02:06:00 by apinho            #+#    #+#             */
/*   Updated: 2016/09/20 15:37:12 by apinho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*str;
	size_t	x;
	size_t	y;

	x = ft_strlen(s);
	str = ft_strnew(x);
	y = 0;
	while (s[y])
	{
		str[y] = (*f)(s[y]);
		y++;
	}
	return (str);
}

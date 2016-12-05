/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinho <apinho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/13 02:06:09 by apinho            #+#    #+#             */
/*   Updated: 2016/09/20 15:37:14 by apinho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	size_t			x;
	size_t			y;
	unsigned int	i;

	x = ft_strlen(s);
	str = ft_strnew(x);
	y = 0;
	i = 0;
	while (s[y])
	{
		str[y] = (*f)(i, s[y]);
		y++;
		i++;
	}
	return (str);
}

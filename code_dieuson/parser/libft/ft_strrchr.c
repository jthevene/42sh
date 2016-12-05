/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinho <apinho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/13 02:07:26 by apinho            #+#    #+#             */
/*   Updated: 2016/09/20 15:37:43 by apinho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char const *s, int c)
{
	char *i;

	i = 0;
	while (*s != '\0')
	{
		if (*s == (char const)c)
			i = (char *)s;
		s++;
	}
	if ((char const)c == *s)
		return ((char *)s);
	return (i);
}

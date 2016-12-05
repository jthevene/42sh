/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinho <apinho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/13 02:02:41 by apinho            #+#    #+#             */
/*   Updated: 2016/09/20 15:36:15 by apinho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char const *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char const)c)
			return ((char *)s);
		s++;
	}
	if ((char const)c == *s)
		return ((char *)s);
	return (NULL);
}

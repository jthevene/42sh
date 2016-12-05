/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinho <apinho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/13 02:06:52 by apinho            #+#    #+#             */
/*   Updated: 2016/10/05 20:23:30 by apinho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, char const *src, size_t n)
{
	int		i;
	char	*x;

	x = dest;
	i = 0;
	if (n > 0 && src[i] != '\0')
	{
		while (n > 0 && src[i] != '\0')
		{
			dest[i] = src[i];
			i++;
			n--;
		}
	}
	if (n > 0)
	{
		while (n > 0)
		{
			dest[i] = '\0';
			i++;
			n--;
		}
	}
	return (x);
}

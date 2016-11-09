/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinho <apinho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/13 02:07:15 by apinho            #+#    #+#             */
/*   Updated: 2016/09/20 15:37:39 by apinho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char const *s1, char const *s2, size_t n)
{
	size_t	i;
	size_t	u;

	u = 0;
	i = 0;
	if (s2[u] == '\0')
		return ((char *)s1);
	while (s1[i] && i < n)
	{
		if (s1[i] == s2[u])
			u++;
		else
			u = 0;
		if (s2[u] == '\0')
			return ((char *)&s1[i - u + 1]);
		i++;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinho <apinho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/13 02:07:53 by apinho            #+#    #+#             */
/*   Updated: 2016/09/20 15:37:51 by apinho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(char const *s1, char const *s2)
{
	int	i;
	int	u;

	i = 0;
	u = 0;
	if (s2[u] == '\0')
		return ((char*)s1);
	while (s1[i])
	{
		u = 0;
		while (s1[i] == s2[u])
		{
			i++;
			u++;
			if (s2[u] == '\0')
				return ((char*)s1 + i - u);
		}
		i++;
	}
	return (NULL);
}

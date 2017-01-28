/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 13:32:36 by sgaudin           #+#    #+#             */
/*   Updated: 2016/02/03 10:32:41 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	unsigned int		i;
	unsigned int		j;
	unsigned int		taille;

	i = 0;
	j = 0;
	taille = ft_strlen(s2);
	if (taille == 0)
		return ((char*)s1);
	while (s1[i] != '\0' && i < n)
	{
		while (s1[i + j] == s2[j] && (i + j) < n)
		{
			if (j == taille - 1)
				return ((char*)s1 + i);
			j++;
		}
		j = 0;
		i++;
	}
	return (NULL);
}

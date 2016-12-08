/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinho <apinho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/13 02:05:31 by hjacque           #+#    #+#             */
/*   Updated: 2016/09/20 15:06:57 by apinho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	lendst;
	size_t	lensrc;
	size_t	tot;
	int		i;

	lendst = ft_strlen(dst);
	lensrc = ft_strlen(src);
	i = 0;
	tot = lensrc + lendst;
	if (size >= lendst)
	{
		while (lendst < (size - 1))
		{
			dst[lendst] = src[i];
			lendst++;
			i++;
		}
		dst[lendst] = '\0';
		return (tot);
	}
	return (size + lensrc);
}

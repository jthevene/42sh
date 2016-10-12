/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthevene <jthevene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/08 16:03:29 by jthevene          #+#    #+#             */
/*   Updated: 2014/11/10 14:33:46 by jthevene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		i;
	size_t		j;

	i = ft_strlen(dst);
	j = ft_strlen(src);
	if (i >= size)
		return (size + j);
	ft_strncat(dst + i, src, size - i - 1);
	return (i + j);
}

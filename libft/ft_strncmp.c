/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthevene <jthevene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 13:54:46 by jthevene          #+#    #+#             */
/*   Updated: 2015/01/07 00:00:28 by jthevene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t		i;

	i = 0;
	if (n == 0)
		return (0);
	while (((unsigned char *)s1)[i] == ((unsigned char *)s2)[i] && \
		s1[i] && s2[i] && i < n - 1)
		i++;
	if (((unsigned char *)s1)[i] > ((unsigned char *)s2)[i])
		return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
	else if (((unsigned char *)s1)[i] < ((unsigned char *)s2)[i])
		return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
	else
		return (0);
}

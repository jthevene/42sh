/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthevene <jthevene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 18:10:34 by jthevene          #+#    #+#             */
/*   Updated: 2015/01/06 23:59:11 by jthevene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	int		i;

	i = 0;
	while (((unsigned char *)s1)[i] == ((unsigned char *)s2)[i] &&
		s1[i] && s2[i])
		i++;
	if (((unsigned char *)s1)[i] > ((unsigned char *)s2)[i])
		return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
	else if (((unsigned char *)s1)[i] < ((unsigned char *)s2)[i])
		return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
	else
		return (0);
}

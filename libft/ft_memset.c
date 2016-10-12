/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthevene <jthevene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 14:55:50 by jthevene          #+#    #+#             */
/*   Updated: 2014/11/07 16:40:45 by jthevene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t		i;
	char		*str;
	char		a;

	str = s;
	a = c;
	i = 0;
	while (i < n)
	{
		str[i] = a;
		i++;
	}
	return (str);
}

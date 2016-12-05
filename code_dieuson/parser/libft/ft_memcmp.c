/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinho <apinho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/13 01:59:14 by apinho            #+#    #+#             */
/*   Updated: 2016/09/20 15:34:17 by apinho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t					i;
	const unsigned char		*scp1;
	const unsigned char		*scp2;

	scp1 = s1;
	scp2 = s2;
	i = 0;
	while (i < n && scp1[i] == scp2[i])
		i++;
	if (i == n)
		return (0);
	return (scp1[i] - scp2[i]);
}

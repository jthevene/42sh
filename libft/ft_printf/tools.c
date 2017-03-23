/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjacque <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/22 15:39:43 by hjacque           #+#    #+#             */
/*   Updated: 2016/01/22 15:39:47 by hjacque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

int		ft_witoa(char *dest, wint_t src)
{
	if (src <= 0x7F)
	{
		dest[3] = (char)src;
		return (1);
	}
	dest[3] = (src & ((1 << 6) - 1)) | 1 << 7;
	if (src <= 0x7FF)
	{
		dest[2] = (src >> 6 | 3 << 6);
		return (2);
	}
	dest[2] = ((src >> 6) & ((1 << 6) - 1)) | 1 << 7;
	if (src <= 0xFFFF)
	{
		dest[1] = (src >> 12 | 7 << 5);
		return (3);
	}
	dest[1] = ((src >> 12) & ((1 << 6) - 1)) | 1 << 7;
	if (src <= 0x10FFFF)
	{
		dest[0] = (src >> 18 | 15 << 4);
		return (4);
	}
	return (-1);
}

size_t	ft_wcharlen(wchar_t *s)
{
	size_t	i;
	char	*tmp;

	if (!(tmp = ft_strnew(4)))
		return (-1);
	i = 0;
	while (*s)
		i += ft_witoa(tmp, (wint_t)*s++);
	free(tmp);
	return (i);
}

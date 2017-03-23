/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjacque <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/22 17:15:44 by hjacque           #+#    #+#             */
/*   Updated: 2016/01/22 17:23:55 by hjacque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

int		conv(const char *format, int *i, va_list *ap)
{
	int	ret;
	int	h;

	ret = 0;
	if (format[*i] == '%')
	{
		if (format[*i + 1] == 0)
			return (0);
		h = printf_call(format, i, ap);
		if (h == -1)
		{
			write(1, format + *i, 1);
			ret++;
			h++;
		}
		ret += h;
	}
	else
	{
		write(1, format + *i, 1);
		ret++;
	}
	return (ret);
}

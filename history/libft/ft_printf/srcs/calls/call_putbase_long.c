/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_putbase_long.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 09:07:37 by sgaudin           #+#    #+#             */
/*   Updated: 2016/03/12 15:56:51 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

int		base_long_2(t_docker *data, uintmax_t result, int base, uint8_t flag)
{
	FT_INIT(int, prec, 0);
	FT_INIT(int, length, data->less == 0 && data->width > 0 ? 1 : 0);
	FT_INIT(int, len_nb, len_base(result, base));
	if (data->dot == 1)
	{
		if (!result && !data->precision && !data->dieze)
			return (0);
		length = data->precision - len_nb;
		prec = data->len;
		data->len = ft_add_spaces(length, data->len, '0');
	}
	if (data->less == 1)
	{
		length = data->width - len_nb;
		length -= prec != 0 ? (data->len - prec) : 0;
		data->len += prec != 0 ? 0 : len_nb;
		ftp_putbase_long(result, base, flag, data);
		data->len = ft_add_spaces(length, data->len, ' ');
		return (0);
	}
	if (!data->less && !data->dot && !data->width && !data->more)
		data->len += TER(!result, 0, (data->dieze ? TER(base == 8, 1, 2) : 0));
	return (1);
}

int		base_long(t_docker *data, uintmax_t result, int base, uint8_t flag)
{
	FT_INIT(int, length, 0);
	FT_INIT(int, len_nb, len_base(result, base));
	if (data->less == 0 && data->width > 0)
	{
		if ((data->precision - len_nb) > 0)
			length -= data->precision - len_nb;
		length += data->width - len_nb - (data->dieze == 1 ? 2 : 0);
		data->len = ft_add_spaces(length, data->len, (data->zero ? '0' : ' '));
	}
	if (base_long_2(data, result, base, flag) == 0)
		return (0);
	data->len += ftp_putbase_long(result, base, flag, data);
	return (0);
}

int		call_putbase_long(const char *str, va_list args, t_docker *data)
{
	uintmax_t	result;

	result = va_arg(args, unsigned long);
	if (str[data->i] == 'O')
		return (base_long(data, result, 8, 'a'));
	else if (str[data->i] == 'U')
		return (base_long(data, result, 10, 'a'));
	else
		return (0);
}

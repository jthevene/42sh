/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_putbase.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 17:58:24 by sgaudin           #+#    #+#             */
/*   Updated: 2016/03/12 16:48:51 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

int		len_base(uintmax_t nb, uint32_t base)
{
	FT_INIT(int, len, 0);
	if (base > 0 && base <= 10)
	{
		if (nb >= base)
			len += len_base((nb / base), base);
		len++;
	}
	else if (base == 16)
	{
		if (nb >= 16)
		{
			len += len_base((nb / 16), base);
			nb %= 16;
		}
		len++;
	}
	return (len);
}

int		putbase_part2(t_docker *data, uintmax_t result, int base, uint8_t flag)
{
	FT_INIT(int, prec, 0);
	FT_INIT(int, length, (data->less == 0 && data->width > 0 ? 1 : 0));
	FT_INIT(int, len_nb, len_base(result, base));
	if (data->dot && !data->precision && !result && base == 8 && data->dieze)
		data->len += ftp_putchar('0');
	if (data->dot == 1)
	{
		if (result == 0 && data->precision == 0)
			return (0);
		data->len += (length == 0) ? len_nb : 0;
		length = data->precision - len_nb;
		prec = data->len;
		data->len = ft_add_spaces(length, data->len, '0');
	}
	if (data->less == 1)
	{
		length = data->width - len_nb - (data->dieze == 1 ?
							TER(base == 8, 1, 2) : 0);
		length -= prec != 0 ? (data->len - prec) : 0;
		data->len += prec != 0 ? 0 : len_nb;
		ftp_putbase(result, base, flag, data);
		data->len = ft_add_spaces(length, data->len, ' ');
		return (0);
	}
	return (1);
}

int		distrib_putbase(t_docker *data, uintmax_t res, int base, uint8_t flag)
{
	FT_INIT(int, length, 0);
	FT_INIT(int, len_nb, len_base(res, base));
	len_nb = data->precision == 0 && res == 0 ? 0 : len_nb;
	if (data->dieze == 1 && base == 16 && res != 0 && (data->zero || data->dot))
		data->len += (ftp_putchar('0') + ftp_putchar(flag + 23));
	if (data->less == 0 && data->width > 0)
	{
		if ((data->precision - len_nb) > 0)
			length -= data->precision - len_nb;
		length += data->width - len_nb - (data->dieze == 1 ?
						TER(base == 16, 2, 1) : 0);
		data->len += len_nb;
		data->len = ft_add_spaces(length, data->len, (data->zero == 1 ?
		'0' : ' '));
	}
	if (data->less == 0 && data->dot == 0 && data->width == 0)
	{
		data->len += TER(res == 0, TER(base == 8 && data->dieze == 1, 0, 1),
			(len_nb + (data->dieze == 1 ? TER(base == 8, 1, 2) : 0)));
		data->len -= (data->dieze == 1 && res != 0 ? TER(base == 8, 1, 2) : 0);
	}
	if (putbase_part2(data, res, base, flag) == 0)
		return (0);
	return (ftp_putbase(res, base, flag, data));
}

int		call_putbase(const char *str, va_list args, t_docker *data)
{
	uintmax_t result;

	result = unsigned_conversion(data, args);
	if (str[data->i] == 'u')
	{
		if (result == 0 && data->precision == 0 && data->width == 0 &&
			data->dot == 1 && data->less == 0)
			return (0);
		return (distrib_putbase(data, result, 10, 'a'));
	}
	else if (str[data->i] == 'o')
		return (distrib_putbase(data, result, 8, 'a'));
	else if (str[data->i] == 'x')
		return (distrib_putbase(data, result, 16, 'a'));
	else if (str[data->i] == 'X')
		return (distrib_putbase(data, result, 16, 'A'));
	else
		return (0);
}

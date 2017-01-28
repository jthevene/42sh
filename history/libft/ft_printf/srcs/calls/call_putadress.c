/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_putadress.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/18 14:29:48 by sgaudin           #+#    #+#             */
/*   Updated: 2016/03/12 15:56:29 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

int		adresse_part2(t_docker *data, uintmax_t result, int base, uint8_t flag)
{
	FT_INIT(int, prec, 0);
	FT_INIT(int, length, data->less == 0 && data->width > 0 ? 1 : 0);
	FT_INIT(int, len_nb, len_base(result, base));
	if (data->dot == 1)
	{
		data->len += ftp_putstr((uint8_t *)"0x");
		if (!result && !data->precision)
			return (0);
		data->len += (length == 0) ? len_nb : 0;
		MULTI(length, prec, data->precision - len_nb);
		data->len = ft_add_spaces(length, data->len, '0');
	}
	if (data->less == 1)
	{
		data->len += !data->dot ? ftp_putstr((uint8_t *)"0x") : 0;
		length = data->width - len_nb - (!result ? 2 : 6);
		length -= prec != 0 ? (data->len - prec) : 0;
		data->len += prec != 0 ? 0 : len_nb;
		ftp_putbase_long(result, base, flag, data);
		data->len = ft_add_spaces(length, data->len, ' ');
		return (0);
	}
	if (data->less == 0 && data->dot == 0 && data->width == 0)
		data->len += len_nb;
	return (1);
}

int		distrib_adresse(t_docker *data, uintmax_t res, int base, uint8_t flag)
{
	FT_INIT(int, length, 0);
	FT_INIT(int, len_nb, len_base(res, base));
	if (data->less == 0 && data->width > 0)
	{
		if ((data->precision - len_nb) > 0)
			length -= data->precision - len_nb;
		length += data->width - len_nb - (data->dieze == 1 ? 2 : 0) - 2;
		data->len += len_nb + (data->dieze == 1 ? 2 : 0);
		data->len += data->zero ? ftp_putstr((uint8_t *)"0x") : 0;
		data->len = ft_add_spaces(length, data->len, (data->zero ? '0' : ' '));
		data->len += !data->dot && !data->zero
					? ftp_putstr((uint8_t *)"0x") : 0;
	}
	if (adresse_part2(data, res, base, flag) == 0)
		return (0);
	ftp_putbase_long(res, base, flag, data);
	return (0);
}

int		call_putadress(const char *str, va_list args, t_docker *data)
{
	FT_INIT(uintmax_t, result, va_arg(args, uintmax_t));
	FT_INIT(int, len, 0);
	if (!data->width && !data->dot)
		data->len += ftp_putstr((uint8_t *)"0x");
	if (str[data->i] == 'p')
		return (distrib_adresse(data, result, 16, 'a'));
	return (len);
}

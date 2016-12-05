/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_putnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 09:10:59 by sgaudin           #+#    #+#             */
/*   Updated: 2016/03/12 17:10:06 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

int		longueur_nb(int64_t nb)
{
	FT_INIT(int, i, 1);
	if (nb < -9223372036854775807)
		return (i);
	i = nb >= 0 ? i : i + 1;
	nb = ft_abs(nb);
	while (nb > 9)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

int		call_putnbr_part2(t_docker *data, int length, int prec, intmax_t res)
{
	data->len += !data->less && data->width > 0 ? longueur_nb(res) : 0;
	if ((data->dot == 1 || data->less == 1) && res < 0 && data->zero == 0)
		ftp_putchar('-');
	data->more == 1 && res >= 0 && data->width != 0 && data->zero == 0
		? ftp_putchar('+') : 0;
	if (data->dot == 1)
	{
		data->len += (length == 0) ? longueur_nb(res) : 0;
		length = data->precision - longueur_nb(res);
		length = res >= 0 ? length : length + 1;
		prec = data->len;
		data->len = ft_add_spaces(length, data->len, '0');
	}
	if (data->less == 1)
	{
		length = data->width - longueur_nb(res) - (data->more
			&& res >= 0 ? 1 : 0) - (prec != 0 ? (data->len - prec) : 0);
		data->len += prec != 0 ? 0 : longueur_nb(res);
		data->len = ftp_putnbr(res, data) +
		ft_add_spaces(length, data->len, data->zero && !data->dot ? '0' : ' ');
		return (0);
	}
	if (data->less == 0 && data->dot == 0 && data->width == 0)
		data->len += longueur_nb(res);
	return (1);
}

int		call_putnbr(const char *str, va_list args, t_docker *data)
{
	FT_INIT(intmax_t, result, signed_conversion(data, args));
	FT_INIT(int, len_nb, longueur_nb(result) +
	(data->more == 1 && result >= 0 ? 1 : 0) + data->space);
	FT_INIT(int, prec, (data->more == 1 && result >= 0
	&& (data->width == 0 || data->zero == 1)) ? ftp_putchar('+') : 0);
	FT_INIT(int, length, 0);
	data->zero == 1 && result < 0 && str ? ftp_putchar('-') : 0;
	if (data->less == 0 && data->width > 0)
	{
		if ((data->precision - len_nb + (result >= 0 ? 0 : 1)) > 0 && data->dot)
			length -= data->precision - len_nb + (result >= 0 ? 0 : 1);
		length += data->width - len_nb + (!result && !data->precision
		&& data->dot ? 1 : 0) - (data->precision && result >= 0 && data->more
		&& !data->zero ? 1 : 0);
		data->len += data->space && !data->dot ? ftp_putchar(' ') : 0;
		data->len = ft_add_spaces(length, data->len,
		(data->zero == 1 && data->dot == 0 ? '0' : ' '));
		length = -1;
	}
	!(data->less + data->dot + data->zero) && result < 0 ? ft_putchar('-') : 0;
	if ((!result && !data->precision && data->dot && !data->less)
		|| call_putnbr_part2(data, length, prec, result) == 0)
		return (0);
	return (ftp_putnbr(result, data));
}

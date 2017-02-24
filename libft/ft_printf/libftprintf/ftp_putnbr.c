/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_putnbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinho <apinho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 18:13:29 by apinho            #+#    #+#             */
/*   Updated: 2017/02/24 18:35:05 by apinho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include <stdio.h>

int		ftp_putnbr(int64_t n, t_docker *data)
{
	if (n < -9223372036854775807)
		return (ftp_putstr((uint8_t *)"9223372036854775808"));
	if (data->space == 1 && data->more == 0
		&& data->precision <= longueur_nb(n) && n > 0)
	{
		data->len += ftp_putchar(' ');
		data->space = 0;
	}
	if (n >= 0 && data->more == 1)
	{
		data->len += 1;
		MULTI(data->more, data->space, 0);
	}
	if (n < 0)
	{
		MULTI(data->more, data->space, 0);
		n = -n;
	}
	if (n >= 10)
		ftp_putnbr((n / 10), data);
	ftp_putchar((n % 10) + '0');
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_putchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinho <apinho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 18:13:29 by apinho            #+#    #+#             */
/*   Updated: 2017/02/24 18:34:55 by apinho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"
#include "../../libftprintf/libftprintf.h"

int		ftp_distrib_char(t_docker *data, int32_t str, int len, int who)
{
	if (who == -1)
	{
		len += ftp_putchar(str);
		return (len = ft_add_spaces((data->width - 1), len,
		data->zero == 1 ? '0' : ' '));
	}
	else if (who == 3)
		len = ft_add_spaces((data->width - 1), len,
		data->zero == 1 || data->dot ? '0' : ' ');
	return (len += ftp_putchar(str));
}

int		call_putchar(const char *str, va_list args, t_docker *data)
{
	int32_t	argument;

	if (data->length == l)
		return (ftp_putwchar(va_arg(args, wint_t), 0));
	else
		argument = va_arg(args, uint32_t);
	if (data->width >= 1 && data->less == 0)
		data->len = ftp_distrib_char(data, argument, data->len, 3);
	else if (data->less == 1 && str)
		data->len = ftp_distrib_char(data, argument, data->len, -1);
	else
		data->len = ftp_distrib_char(data, argument, data->len, 4);
	return (0);
}

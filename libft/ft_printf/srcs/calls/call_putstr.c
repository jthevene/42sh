/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_putstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinho <apinho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 18:13:29 by apinho            #+#    #+#             */
/*   Updated: 2017/02/24 18:34:53 by apinho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"
#include "../../libftprintf/libftprintf.h"

int					ftp_dot(uint8_t *str, unsigned int len)
{
	int				i;

	i = 0;
	if (str)
	{
		while (str[i] && i < ftp_strlen(str) && i < (int)len)
		{
			ft_putchar(str[i]);
			i++;
		}
	}
	return (i);
}

int					ftp_distrib(t_docker *data, uint8_t *str, int len, int who)
{
	FT_INIT(int, ref, len);
	FT_INIT(char, c, data->zero == 1 ? '0' : ' ');
	if (who == -1)
	{
		len += ftp_putstr(str);
		return (len = ft_add_spaces((data->width - ftp_strlen(str)), len, c));
	}
	else if (who == 0)
		return (len += ftp_dot(str, data->precision));
	else if (who == 1)
	{
		len += ftp_dot(str, data->precision);
		return (len = ft_add_spaces((data->width - (len - ref)), len, c));
	}
	else if (who == 2)
	{
		c = !str ? '0' : c;
		if ((len = ft_add_spaces(data->width - (ftp_strlen(str) >
		data->precision ? data->precision : ftp_strlen(str)), len, c)) >= 0)
			return (len += ftp_dot(str, data->precision));
	}
	else if (who == 3)
		len = ft_add_spaces((data->width - ftp_strlen(str)), len, c);
	return (len += ftp_putstr(str));
}

int					call_putstr(const char *str, va_list args, t_docker *data)
{
	uint8_t *argument;

	if (data->length == l)
		return (ftp_putwstr(va_arg(args, wchar_t *), 0));
	else
		argument = va_arg(args, uint8_t *);
	if (argument == NULL && !data->width && !data->dot && data->less)
	{
		data->len += ftp_putstr((uint8_t *)"(null)");
		return (0);
	}
	if (data->width >= 1 && data->dot == 0 && data->less == 0)
		data->len = ftp_distrib(data, argument, data->len, 3);
	else if (data->dot == 1 && data->less == 1)
		data->len = ftp_distrib(data, argument, data->len, 1);
	else if (data->less == 1 && str && data->dot == 0)
		data->len = ftp_distrib(data, argument, data->len, -1);
	else if (data->width >= 1 && data->dot == 1 && data->less == 0)
		data->len = ftp_distrib(data, argument, data->len, 2);
	else if (data->dot == 1 && data->less == 0 && data->width == 0)
		data->len = ftp_distrib(data, argument, data->len, 0);
	else
		data->len = ftp_distrib(data, argument, data->len, 4);
	return (0);
}

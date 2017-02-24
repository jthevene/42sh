/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_purcent.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinho <apinho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 18:13:29 by apinho            #+#    #+#             */
/*   Updated: 2017/02/24 18:34:59 by apinho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

int			ftp_purcent(t_docker *data, int32_t str, int len, int who)
{
	char		c;

	c = data->zero ? '0' : ' ';
	if (who == -1)
	{
		len += ftp_putchar(str);
		return (len = ft_add_spaces((data->width - 1), len,
									data->zero == 1 ? '0' : ' '));
	}
	else if (who == 3)
	{
		if (data->dot == 1)
			c = '0';
		len = ft_add_spaces((data->width - 1), len, c);
	}
	return (len += str ? ftp_putchar(str) : 0);
}

int			call_purcent(const char *str, va_list args, t_docker *data)
{
	int32_t argument;

	if (args)
		argument = data->type;
	if (data->width >= 1 && data->less == 0)
		data->len = ftp_purcent(data, argument, data->len, 3);
	else if (data->less == 1 && str)
		data->len = ftp_purcent(data, argument, data->len, -1);
	else
		data->len = ftp_purcent(data, argument, data->len, 4);
	return (0);
}

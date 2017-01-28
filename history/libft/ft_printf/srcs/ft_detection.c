/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_detection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 11:13:38 by sgaudin           #+#    #+#             */
/*   Updated: 2016/03/14 11:13:39 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include <stdio.h>

void			ft_detect_flags(const char *str, t_docker *d)
{
	if (ft_strchr("#0123456789-+ .", str[d->i]))
	{
		d->dieze = (str[d->i] == '#')
			? 1 : d->dieze;
		d->more = str[d->i] == '+' ? 1 : d->more;
		d->zero = (str[d->i] == '0' && ft_strchr(" +%#", str[d->i - 1]))
			? 1 : d->zero;
		d->space = (str[d->i] == ' ' && ft_strchr("%0", str[d->i - 1]))
			? 1 : d->space;
		if (str[d->i] == '.')
		{
			d->result = 0;
			MULTI(d->choice, d->dot, 1);
		}
		if (str[d->i] == '-')
		{
			MULTI(d->result, d->zero, 0);
			d->choice = -1;
			d->less = 1;
		}
		ft_detect_width(str, d, d->choice);
		d->i++;
		str[d->i] != '\0' ? ft_detect_flags(str, d) : 0;
	}
}

void			ft_detect_width(const char *str, t_docker *data, int who)
{
	if (str[data->i] >= '0' && str[data->i] <= '9')
	{
		data->result = data->result * 10 + (str[data->i] - 48);
		if (who == -1 || who == 0)
			data->width = data->result;
		else if (who == 1)
		{
			data->dot = 1;
			data->precision = data->result;
		}
	}
}

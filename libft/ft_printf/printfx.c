/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printfx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjacque <hjacque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/03 11:30:18 by hjacque           #+#    #+#             */
/*   Updated: 2016/01/25 13:53:23 by hjacque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

int						printf_x(va_list *ap, int *state)
{
	unsigned long long	value;
	int					ret;

	value = get_uarg(ap, state);
	state[PRECISION] = (state[ZERO]) ? state[CHAMP] : state[PRECISION];
	ret = (state[6] > ft_unbrlen(value, 16)) ? state[6] : ft_unbrlen(value, 16);
	state[CHAMP] = (state[DIEZ] != 0) ? state[CHAMP] - 2 : state[CHAMP];
	ret = shortf(ret, state);
	if (state[DIEZ] != 0 && value)
	{
		write(1, "0x", 2);
		ret = ret + 2;
	}
	if (state[PRECISION] == 0 && value == 0)
		return (ret - 1);
	ft_putunbrprec(value, state, 16, 0);
	state[CHAMP] = (state[DIEZ] != 0) ? state[CHAMP] + 2 : state[CHAMP];
	if (ret < state[CHAMP] && state[MINUS] != 0)
		while (ret < state[CHAMP])
		{
			(void)write(1, " ", 1);
			ret++;
		}
	return (ret);
}

int						printf_gx(va_list *ap, int *state)
{
	unsigned long long	value;
	int					ret;

	value = get_uarg(ap, state);
	state[PRECISION] = (state[ZERO]) ? state[CHAMP] : state[PRECISION];
	ret = (state[6] > ft_unbrlen(value, 16)) ? state[6] : ft_unbrlen(value, 16);
	state[CHAMP] = (state[DIEZ] != 0) ? state[CHAMP] - 2 : state[CHAMP];
	ret = shortf(ret, state);
	if (state[DIEZ] != 0 && value != 0)
	{
		write(1, "0X", 2);
		ret = ret + 2;
	}
	if (state[PRECISION] == 0 && value == 0)
		return (ret - 1);
	ft_putunbrprec(value, state, 16, 1);
	if (ret < state[CHAMP] && state[MINUS] != 0)
		while (ret < state[CHAMP])
		{
			(void)write(1, " ", 1);
			ret++;
		}
	return (ret);
}

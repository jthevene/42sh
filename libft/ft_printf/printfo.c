/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printfo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjacque <hjacque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/03 11:30:18 by hjacque           #+#    #+#             */
/*   Updated: 2016/01/22 15:42:38 by hjacque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

int						printf_o(va_list *ap, int *state)
{
	unsigned long long	value;
	int					ret;

	value = get_uarg(ap, state);
	state[PRECISION] = (state[ZERO]) ? state[CHAMP] : state[PRECISION];
	ret = ft_unbrlen(value, 8);
	ret = (state[PRECISION] > ret) ? state[PRECISION] : ret;
	if (ret < state[CHAMP] && state[MINUS] == 0)
		while (ret++ < state[CHAMP])
			(void)write(1, " ", 1);
	if (state[DIEZ] != 0 && value != 0)
	{
		write(1, "0", 1);
		ret++;
	}
	if (state[PRECISION] == 0 && value == 0 && state[DIEZ] == 0)
		return (ret - 1);
	ft_putunbrprec(value, state, 8, 0);
	if (ret < state[CHAMP] && state[MINUS] != 0)
		while (ret++ < state[CHAMP])
			(void)write(1, " ", 1);
	if (state[CHAMP] > state[PRECISION])
		if (ft_unbrlen(value, 8) < state[CHAMP])
			ret--;
	return (ret);
}

int						printf_go(va_list *ap, int *state)
{
	unsigned long long	value;
	int					ret;

	state[L] = 1;
	value = get_uarg(ap, state);
	if (state[ZERO])
		state[PRECISION] = state[CHAMP];
	ret = ft_unbrlen(value, 8);
	ret = (state[PRECISION] > ret) ? state[PRECISION] : ret;
	if (ret < state[CHAMP] && state[MINUS] == 0)
		while (ret++ < state[CHAMP])
			(void)write(1, " ", 1);
	if (state[DIEZ] != 0 && value != 0)
	{
		write(1, "0", 1);
		ret++;
	}
	if (state[PRECISION] == 0 && value == 0)
		return (ret - 1);
	ft_putunbrprec(value, state, 8, 0);
	if (ret < state[CHAMP] && state[MINUS] != 0)
		while (ret++ < state[CHAMP])
			(void)write(1, " ", 1);
	ret = (state[CHAMP] > state[PRECISION]) ? ret-- : ret;
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printfd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/03 11:30:18 by hjacque           #+#    #+#             */
/*   Updated: 2017/03/23 18:14:44 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

int				printf_d(va_list *ap, int *state)
{
	long long	value;
	int			ret;

	value = get_arg(ap, state);
	if (state[ZERO])
		state[PRECISION] = (value >= 0) ? state[CHAMP] : state[CHAMP] - 1;
	if (state[PLUS])
	{
		state[CHAMP]--;
		state[PRECISION]--;
	}
	ret = (state[6] > ft_nbrlen(value)) ? state[6] : ft_nbrlen(value);
	ret = (value < 0 || (state[PLUS] != 0 || state[4] != 0)) ? ret + 1 : ret;
	ret = shortf(ret, state);
	if (state[PRECISION] == 0 && value == 0)
		return (ret - 1);
	ft_putnbrprec(value, state, 0);
	if (ret < state[CHAMP] && state[MINUS] != 0)
		while (ret < state[CHAMP])
		{
			(void)write(1, " ", 1);
			ret++;
		}
	ret = (state[SPACE] && state[ZERO]) ? ret - 1 : ret;
	return (ret);
}

int				printf_gd(va_list *ap, int *state)
{
	long long	value;
	int			ret;

	state[L] = 1;
	value = get_arg(ap, state);
	if (state[ZERO])
		state[PRECISION] = (value >= 0) ? state[CHAMP] : state[CHAMP] - 1;
	ret = ft_nbrlen(value);
	ret = (state[PRECISION] > ret) ? state[PRECISION] : ret;
	if (value < 0 || (state[PLUS] != 0 || state[SPACE] != 0))
		++ret;
	if (ret < state[CHAMP] && state[MINUS] == 0)
		while (ret < state[CHAMP])
		{
			(void)write(1, " ", 1);
			ret++;
		}
	ft_putnbrprec(value, state, 0);
	if (ret < state[CHAMP] && state[MINUS] != 0)
		while (ret++ < state[CHAMP])
			(void)write(1, " ", 1);
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printfc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjacque <hjacque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/03 11:30:18 by hjacque           #+#    #+#             */
/*   Updated: 2016/01/22 15:47:52 by hjacque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

int			printf_c(va_list *ap, int *state)
{
	int		ret;
	int		tmp;
	int		param;
	char	c;

	c = (state[ZERO]) ? '0' : ' ';
	tmp = -1;
	if (state[L])
		return (printf_gc(ap, state));
	ret = 1;
	param = (char)va_arg(*ap, int);
	if (state[PRECISION] != -1)
		ret = (state[PRECISION] < ret + 1) ? state[PRECISION] : ret;
	while (state[CHAMP] > ret)
	{
		(void)write(1, &c, 1);
		ret++;
	}
	if (state[ZERO] && (state[CHAMP] > ret))
		while (tmp++ < state[CHAMP] - ret)
			(void)write(1, "0", 1);
	if (state[PRECISION] == 0 && param == 0)
		return (1);
	(void)write(1, &param, 1);
	return (ret);
}

int			printf_gc(va_list *ap, int *state)
{
	int		ret;
	wint_t	param;
	int		tmp;
	char	dest[4];

	tmp = state[PRECISION];
	param = va_arg(*ap, wint_t);
	ret = ft_witoa(dest, param);
	write(1, dest + (4 - ret), ret);
	return (ret);
}

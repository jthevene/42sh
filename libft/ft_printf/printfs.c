/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printfs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjacque <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/22 15:14:20 by hjacque           #+#    #+#             */
/*   Updated: 2016/01/22 16:39:08 by hjacque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

int			printf_s(va_list *ap, int *state)
{
	int		ret;
	void	*param;
	char	c;
	int		i;

	i = -1;
	c = (state[ZERO] != 0) ? '0' : ' ';
	if (state[L])
		return (printf_gs(ap, state));
	param = va_arg(*ap, char *);
	if (param == NULL)
	{
		ret = 6;
		param = "(null)";
	}
	else
		ret = ft_strlen(param);
	if (state[PRECISION] != -1)
		ret = (state[PRECISION] < ret + 1) ? state[PRECISION] : ret;
	while (state[CHAMP] - ret > ++i)
		write(1, &c, 1);
	write(1, param, ret);
	return (ret + i);
}

int			printf_gs(va_list *ap, int *state)
{
	int		ret;
	int		rt;
	wchar_t	*param;
	int		i;
	char	dest[4];

	rt = 0;
	i = -1;
	param = va_arg(*ap, wchar_t *);
	if (param == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (*param)
	{
		ret = ft_witoa(dest, *param);
		rt = ret + rt;
		write(1, dest + (4 - ret), ret);
		param++;
	}
	ret = (state[6] != -1 && state[6] < ret + 1) ? state[6] : ret + 1;
	while (state[CHAMP] - ret > ++i)
		write(1, " ", 1);
	return (rt);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjacque <hjacque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/03 11:08:40 by hjacque           #+#    #+#             */
/*   Updated: 2016/01/22 17:27:34 by hjacque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

const	t_printf	g_printf[] =
{
	{'s', printf_s},
	{'d', printf_d},
	{'S', printf_gs},
	{'p', printf_p},
	{'D', printf_gd},
	{'i', printf_i},
	{'o', printf_o},
	{'O', printf_go},
	{'u', printf_u},
	{'U', printf_gu},
	{'x', printf_x},
	{'X', printf_gx},
	{'c', printf_c},
	{'C', printf_gc},
	{'%', printf_pourcent},
	{0, NULL}
};

int			indexof(const char *str, const char c)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			return (i);
	}
	return (-1);
}

int			printf_call(const char *str, int *i, va_list *ap)
{
	int		p;
	int		state[13];

	p = -1;
	while (++p < 13)
		state[p] = 0;
	state[CHAMP] = -1;
	state[PRECISION] = -1;
	p = 0;
	*i += 1;
	while (str[*i] && p != -1)
		range(state, str, &p, i);
	p = -1;
	while (g_printf[++p].c)
		if (g_printf[p].c == str[*i])
			return (g_printf[p].ptr(ap, state));
	return (-1);
}

int			ft_printf(const char *format, ...)
{
	int		i;
	va_list	ap;
	int		ret;

	ret = 0;
	va_start(ap, format);
	i = -1;
	while (format[++i])
		ret += conv(format, &i, &ap);
	return (ret);
}

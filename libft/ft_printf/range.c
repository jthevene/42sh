/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   range.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjacque <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/22 17:07:39 by hjacque           #+#    #+#             */
/*   Updated: 2016/01/22 17:11:33 by hjacque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

void	range(int *state, const char *str, int *p, int *i)
{
	if ((*p = indexof("#0-+  .hhlljz", str[*i])) != -1)
	{
		if ((*p == 7 || *p == 9) && state[*p])
			state[++*p] = 1;
		else if (*p == 6)
			state[*p] = get_nb(str, i);
		else
			state[*p] = 1;
		*i = (*p != 6) ? *i + 1 : *i;
	}
	else if (str[*i] >= '0' && str[*i] <= '9')
	{
		state[CHAMP] = get_nb(str, i);
		*p = 0;
	}
}

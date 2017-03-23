/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printfpourcent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/03 11:30:18 by hjacque           #+#    #+#             */
/*   Updated: 2017/03/23 17:59:21 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

int			printf_pourcent(va_list *ap, int *state)
{
	char	c;
	int		ret;
	int		tmp;
	int		i;

	(void)ap;
	i = 0;
	ret = 1;
	c = (state[ZERO]) ? '0' : ' ';
	if (state[PRECISION] != -1)
		ret = (state[PRECISION] < ret + 1) ? state[PRECISION] : ret;
	tmp = state[CHAMP] - ret - 1;
	while (tmp-- > 0)
	{
		write(1, &c, 1);
		i++;
	}
	write(1, "%", 1);
	if (state[PRECISION] < state[CHAMP])
		ret++;
	return (ret + i);
}

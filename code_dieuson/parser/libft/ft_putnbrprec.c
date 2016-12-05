/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrprec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinho <apinho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/04 13:24:41 by apinho            #+#    #+#             */
/*   Updated: 2016/09/20 15:35:35 by apinho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbrprec(long long nbr, int *state, int base, int caps)
{
	int	useme;
	int	ret;

	ret = ft_nbrlen(nbr, base);
	useme = -1;
	if (nbr < 0)
		(void)write(1, "-", 1);
	else if (state[3] != 0)
		(void)write(1, "+", 1);
	else if (state[3] != 0 && nbr == 0)
		(void)write(1, " ", 1);
	else if (state[4] != 0)
	{
		(void)write(1, " ", 1);
		state[6]--;
	}
	if (state[6] > ret)
		while (++useme != state[6] - ret)
			(void)write(1, "0", 1);
	ft_putnbrchelou(nbr, base, caps);
}

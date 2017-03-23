/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrprec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/04 13:24:41 by hjacque           #+#    #+#             */
/*   Updated: 2017/03/23 18:42:21 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbrprec(long long nbr, int *state, int caps)
{
	int	useme;
	int	ret;

	ret = ft_nbrlen(nbr);
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
	ft_putnbr_ftprintf(nbr, caps);
}

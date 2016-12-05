/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrulong.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinho <apinho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 13:50:26 by apinho            #+#    #+#             */
/*   Updated: 2016/09/20 15:35:40 by apinho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_unbrlen(unsigned long long nbr, unsigned int base)
{
	int		len;

	len = 1;
	while (nbr > (base - 1))
	{
		nbr = nbr / base;
		len++;
	}
	return (len);
}

void		ft_putunbrprec(unsigned long long nbr, int *state, \
						unsigned int base, int caps)
{
	int		useme;
	int		ret;

	ret = ft_unbrlen(nbr, base);
	useme = -1;
	if (state[6] > ret)
		while (++useme != state[6] - ret)
			(void)write(1, "0", 1);
	ft_putunbrchelou(nbr, base, caps);
}

void		ft_putunbrchelou(unsigned long long nbr, unsigned int base, \
							int caps)
{
	char	c;

	if (nbr > base - 1)
		ft_putunbrchelou(nbr / base, base, caps);
	c = nbr % base;
	if (c > 9 && caps == 0)
		c = c - 10 + 'a';
	else if (c > 9 && caps == 1)
		c = c - 10 + 'A';
	else
		c = c + '0';
	(void)write(1, &c, 1);
}

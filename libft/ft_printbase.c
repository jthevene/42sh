/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printbits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 15:08:07 by sgaudin           #+#    #+#             */
/*   Updated: 2016/02/03 10:25:58 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_printbase(unsigned char n, int base)
{
	if (base > 0 && base <= 10)
	{
		if (n >= base)
			ft_printbase((n / base), base);
		ft_putchar((n % base) + '0');
	}
}

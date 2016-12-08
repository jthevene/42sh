/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinho <apinho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/03 13:49:34 by apinho            #+#    #+#             */
/*   Updated: 2016/09/20 15:34:40 by apinho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_nbrlen(long long nbr, int base)
{
	int	len;

	len = 1;
	while (nbr > (base - 1) || nbr < -(base - 1))
	{
		nbr = nbr / base;
		len++;
	}
	return (len);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive_pow.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/08 14:33:50 by sgaudin           #+#    #+#             */
/*   Updated: 2016/02/08 16:35:43 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"
#include <stdio.h>

int		ft_recursive_pow(int n, int power)
{
	int result;

	result = n;
	if (power == 0)
		return (1);
	else if (power < 0)
		return (0);
	if (n == 0)
		return (0);
	result = result * ft_recursive_pow(n, power - 1);
	return (result);
}

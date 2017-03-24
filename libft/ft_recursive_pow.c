/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive_pow.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 18:13:29 by hjacque           #+#    #+#             */
/*   Updated: 2017/03/24 09:50:33 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjacque <hjacque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 18:13:29 by hjacque           #+#    #+#             */
/*   Updated: 2017/03/08 14:51:30 by hjacque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		size_bin(unsigned int nbr)
{
	if (nbr <= 64)
		return (1);
	else if (nbr <= 1024)
		return (2);
	else if (nbr <= 32768)
		return (3);
	else
		return (4);
}

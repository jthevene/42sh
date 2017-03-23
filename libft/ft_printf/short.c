/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjacque <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 13:47:29 by hjacque           #+#    #+#             */
/*   Updated: 2016/01/25 13:49:15 by hjacque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

int		shortf(int ret, int *state)
{
	if (ret < state[CHAMP] && state[MINUS] == 0)
		while (ret < state[CHAMP])
		{
			(void)write(1, " ", 1);
			ret++;
		}
	return (ret);
}

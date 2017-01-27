/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_spaces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 14:54:20 by sgaudin           #+#    #+#             */
/*   Updated: 2016/03/10 15:05:19 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

int			ft_add_spaces(int nb_spaces, int len, char c)
{
	if (nb_spaces > 0)
	{
		while (nb_spaces > 0)
		{
			ft_putchar(c);
			nb_spaces--;
			len++;
		}
	}
	return (len);
}

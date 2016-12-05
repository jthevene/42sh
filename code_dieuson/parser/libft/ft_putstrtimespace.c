/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrtimespace.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinho <apinho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/13 02:02:09 by apinho            #+#    #+#             */
/*   Updated: 2016/09/20 15:36:01 by apinho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putstrtimespace(char const *s)
{
	int	x;

	x = 0;
	while (x < 4)
		x++;
	while (x < 16)
	{
		ft_putchar(s[x]);
		x++;
	}
	ft_putchar(' ');
}

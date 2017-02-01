/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 09:26:40 by jules             #+#    #+#             */
/*   Updated: 2017/01/30 11:21:38 by jthevene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/history.h"

void	ft_error(char *str)
{
	ft_putstr("42sh: ");
	ft_putstr(str);
	ft_putstr(": ");
	ft_putendl(strerror(errno));
}

void	ft_out_of_range(int i)
{
	ft_putstr("history: ");
	ft_putnbr(i);
	ft_putendl(": history position out of range");
}
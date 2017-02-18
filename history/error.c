/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 09:26:40 by jules             #+#    #+#             */
/*   Updated: 2017/02/18 15:42:05 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/history.h"

void	ft_error(char *str)
{
	ft_putstr_fd("21sh: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
}

void	ft_out_of_range(int i)
{
	ft_putstr_fd("history: ", 2);
	ft_putnbr_fd(i, 2);
	ft_putendl_fd(": history position out of range", 2);
}

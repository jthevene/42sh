/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_putwchar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/08 17:38:25 by sgaudin           #+#    #+#             */
/*   Updated: 2016/06/29 16:09:56 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"
#include "../../libftprintf/libftprintf.h"

int		call_putwchar(const char *str, va_list args, t_docker *data)
{
	wchar_t result;

	result = va_arg(args, wchar_t);
	if (str[data->i] == 'C')
		return (ftp_putwchar(result, 0));
	else
		return (0);
}

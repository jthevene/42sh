/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_putwchar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinho <apinho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 18:13:29 by apinho            #+#    #+#             */
/*   Updated: 2017/02/24 18:34:52 by apinho           ###   ########.fr       */
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

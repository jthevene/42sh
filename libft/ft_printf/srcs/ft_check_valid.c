/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_valid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinho <apinho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 18:13:29 by apinho            #+#    #+#             */
/*   Updated: 2017/02/24 18:34:49 by apinho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		detect(const char *s, t_docker *data)
{
	data->i++;
	if ((s[data->i] == ' ' && s[data->i + 1] == ' ')
		|| (s[data->i] == ' ' && s[data->i + 1] == '%'))
	{
		while (s[data->i] != '\0' && s[data->i] == ' ')
			data->i++;
		if (s[data->i] == '%')
			return (1);
	}
	if (s[data->i] == 's' || s[data->i] == 'S' || s[data->i] == 'p'
		|| s[data->i] == 'd' || s[data->i] == 'D' || s[data->i] == 'i'
		|| s[data->i] == 'o' || s[data->i] == 'O' || s[data->i] == 'u'
		|| s[data->i] == 'U' || s[data->i] == 'x' || s[data->i] == 'X'
		|| s[data->i] == 'c' || s[data->i] == 'C' || s[data->i] == '%'
		|| s[data->i] == '#' || s[data->i] == '0' || s[data->i] == '-'
		|| s[data->i] == '+' || s[data->i] == 'h' || s[data->i] == 'l'
		|| s[data->i] == 'j' || s[data->i] == 'z' || s[data->i] == '.'
		|| (s[data->i] >= '0' && s[data->i] <= '9')
		|| (s[data->i] == ' ' && s[data->i - 1] == '%'))
		return (1);
	else
		return (0);
}

int		ft_check_valid(const char *str, t_docker *data)
{
	if (ft_strchr("sSpdDioOuUxXcC%", str[data->i]) && str[data->i])
	{
		if (!ft_strchr("S", str[data->i]))
			data->zero = data->dot && data->zero ? 0 : data->zero;
		return (1);
	}
	else
		return (0);
}

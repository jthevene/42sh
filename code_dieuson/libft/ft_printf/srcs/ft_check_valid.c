/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_valid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 16:54:43 by sgaudin           #+#    #+#             */
/*   Updated: 2016/03/12 16:51:25 by sgaudin          ###   ########.fr       */
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

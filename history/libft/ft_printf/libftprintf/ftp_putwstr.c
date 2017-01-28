/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_putwstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 16:05:18 by sgaudin           #+#    #+#             */
/*   Updated: 2016/06/29 16:40:39 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include "libftprintf.h"

int		ftp_putwstr(wchar_t *str, int write)
{
	int len;
	int i;

	len = 0;
	i = 0;
	if (!str)
	{
		ft_putstr("(null)");
		return (6);
	}
	while (str[i] && str != NULL)
	{
		len += ftp_putwchar(str[i], write);
		i++;
	}
	return (len);
}

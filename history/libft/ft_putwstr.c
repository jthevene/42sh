/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/08 17:00:37 by sgaudin           #+#    #+#             */
/*   Updated: 2016/02/08 17:32:41 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int		ft_putwstr(wchar_t *str)
{
	int len;

	len = 0;
	while (*str)
	{
		len += ft_putwchar(*str);
		str++;
	}
	return (len);
}

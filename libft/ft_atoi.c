/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthevene <jthevene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 15:31:29 by jthevene          #+#    #+#             */
/*   Updated: 2014/11/10 14:25:14 by jthevene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		atoi_ignored(char c)
{
	return (c == '\n' || c == '\v' || c == '\t' || c == '\r' || c == '\f'
	|| c == ' ');
}

int		ft_atoi(const char *str)
{
	int		i;
	int		result;

	i = 0;
	result = 0;
	while (atoi_ignored(*str))
		str++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	if (str[0] == '-')
		return (-result);
	return (result);
}

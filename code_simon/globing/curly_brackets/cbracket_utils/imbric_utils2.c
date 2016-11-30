/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imbric_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 10:27:41 by sgaudin           #+#    #+#             */
/*   Updated: 2016/11/30 10:27:41 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/globing.h"

int				i_detect_imbric(char *str)
{
	FT_INIT(int, i, 0);
	FT_INIT(int, j, 0);
	FT_INIT(int, count, 0);
	while (str[i])
	{
		if (str[i] == '{')
		{
			j = i + 1;
			count = 0;
			while (str[j] != '}')
			{
				if (str[j] == '{')
					return (count);
				count++;
				j++;
			}
		}
		i++;
	}
	return (-1);
}
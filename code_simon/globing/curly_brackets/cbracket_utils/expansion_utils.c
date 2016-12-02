/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 11:24:12 by sgaudin           #+#    #+#             */
/*   Updated: 2016/12/02 11:24:13 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/globing.h"

int			exp_type(char *str)
{
	FT_INIT(int, i, 0);
	FT_INIT(int, chars, 0);
	FT_INIT(int, digit, 0);
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			digit = 1;
		else
			chars = 1;
		i++;
	}
	if (digit && chars)
		return (BOTH);
	else if (digit && !chars)
		return (DIGIT);
	else if (!digit && chars)
		return (CHARS);
	return (BOTH);
}
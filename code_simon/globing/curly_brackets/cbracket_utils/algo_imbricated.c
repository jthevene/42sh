/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_imbricated.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 09:54:32 by sgaudin           #+#    #+#             */
/*   Updated: 2016/11/23 09:54:33 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/globing.h"

int			last_bracket(char *str)
{
	FT_INIT(int, i, 0);
	FT_INIT(int, ret, 0);
	while (str[i])
		i++;
	--i;
	ret = i;
	printf("ret = %d i = %d\n", ret, i);
	while (str[i] != '{')
	{
		i--;
		ret--;
	}
	printf("ret[i] = %c %d\n", str[ret], ret);
	return (ret);
}
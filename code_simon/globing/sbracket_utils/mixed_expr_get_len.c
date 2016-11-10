/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mixed_expr_get_len.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 15:13:11 by sgaudin           #+#    #+#             */
/*   Updated: 2016/11/10 15:13:12 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/globing.h"

static int 	debut_case(char *str)
{
	FT_INIT(int, i, 1);
	FT_INIT(int, len, 1);
	while (str[len] && str[len] != '[' && str[len + 1] != ':')
		len++;
	i = len;
	while (str[i])
	{
		if (str[i - 1] == ']' && str[i - 2] == ':')
			break ;
		i++;
	}
	if (str[i] && str[i] != ']')
	{
		while (str[i])
		{
			i++;
			len++;
		}
	}
	else
		len++;
	return (len);
}

static int 	fin_case(char *str)
{
	FT_INIT(int, i, 0);
	FT_INIT(int, len, 0);
	while (str[i])
	{
		if (str[i + 1] == ':' && str[i + 2] == ']')
		{
			i += 2;
			break ;
		}
		i++;
	}
	while (str[i])
	{
		i++;
		len++;
	}
	return (len);
}

int 		mixed_expr_get_len(char *str, int pos)
{
	FT_INIT(int, len, 0);
	if (pos == DEBUT)
		len = debut_case(str);
	else if (pos == FIN)
		len = fin_case(str);
	return (len);
}

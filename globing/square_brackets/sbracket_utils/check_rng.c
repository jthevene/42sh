/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rng.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinho <apinho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 18:13:29 by apinho            #+#    #+#             */
/*   Updated: 2017/02/24 18:37:30 by apinho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/globing.h"
#include "../../../includes/redir.h"

int			check_rng(char *str)
{
	FT_INIT(int, i, 0);
	FT_INIT(char *, tmp, clean_brackets(str));
	if (!ft_strchr(tmp, '-'))
	{
		free(tmp);
		return (1);
	}
	while (tmp[i])
	{
		if (tmp[i] == '-' && tmp[i - 1] && tmp[i + 1]
			&& tmp[i + 1] != ']' && tmp[i - 1] != '[')
		{
			if (tmp[i - 1] > tmp[i + 1])
			{
				free(tmp);
				return (0);
			}
			i++;
		}
		i++;
	}
	free(tmp);
	return (1);
}

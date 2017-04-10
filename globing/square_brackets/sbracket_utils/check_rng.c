/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rng.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 16:54:44 by sgaudin           #+#    #+#             */
/*   Updated: 2017/04/10 14:58:04 by sgaudin          ###   ########.fr       */
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

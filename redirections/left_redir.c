/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 15:18:50 by sgaudin           #+#    #+#             */
/*   Updated: 2017/04/10 14:58:50 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh42.h"

int		is_left_redir(char *str)
{
	FT_INIT(int, i, 0);
	FT_INIT(int, start, 0);
	FT_INIT(char *, filename, NULL);
	while (str[i])
	{
		if (str[i] == '<')
		{
			if (str[i + 1] == '<')
				return (0);
		}
		i++;
	}
	if (str[i] == ' ')
		i++;
	start = i;
	while (str[i] && str[i] != ' ')
		i++;
	if (start == i)
		return (0);
}

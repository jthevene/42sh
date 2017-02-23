/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 16:03:44 by jules             #+#    #+#             */
/*   Updated: 2017/02/23 15:12:56 by jthevene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

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

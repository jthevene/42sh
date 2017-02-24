/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_brackets.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinho <apinho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 18:13:29 by apinho            #+#    #+#             */
/*   Updated: 2017/02/24 18:35:57 by apinho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/globing.h"
#include "../../../includes/redir.h"

int				count_brackets(char *str, char bracket)
{
	FT_INIT(int, i, 0);
	FT_INIT(int, count, 0);
	FT_INIT(int, count_close, 0);
	FT_INIT(char, close, bracket == '[' ? ']' : '}');
	while (str[i])
	{
		if (str[i] == bracket)
		{
			if ((i > 0 && str[i - 1] != '\\') || i == 0)
				count++;
		}
		else if (str[i] == close)
		{
			if ((i > 0 && str[i - 1] != '\\') || i == 0)
				count_close++;
		}
		i++;
	}
	if (count != count_close)
		return (0);
	return (1);
}

int				next_bracket(char *str, char c, int i)
{
	FT_INIT(int, count, 0);
	FT_INIT(int, ret, 0);
	FT_INIT(int, c2, c == '[' ? ']' : '}');
	while (str[i])
	{
		if (str[i] == c)
			count++;
		if (str[i] == c2)
		{
			count--;
			if (!count)
				break ;
		}
		i++;
		ret++;
	}
	return (ret);
}

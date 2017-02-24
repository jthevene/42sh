/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commas_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinho <apinho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 18:13:29 by apinho            #+#    #+#             */
/*   Updated: 2017/02/24 18:36:38 by apinho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/globing.h"

int		count_commas(char *line, int i)
{
	FT_INIT(int, count, 0);
	FT_INIT(int, tmp, 0);
	while (line[i])
	{
		if (line[i] == ',')
			count++;
		if (line[i] == '{')
		{
			if (!(tmp = count_commas(line, i + 1)))
				return (0);
			else
				count += tmp;
			i += next_bracket(line, '{', i + 1);
		}
		if (line[i] == '}')
			return (count);
		i++;
	}
	return (count);
}

int		check_commas(char *line, int i)
{
	FT_INIT(int, commas, count_commas(line, i));
	if (!commas)
		return (0);
	else if (commas == 1)
	{
		while (line[i] != ',')
			i++;
		return (line[i + 1] != '}' ? 1 : 0);
	}
	while (line[++i])
	{
		if (line[i] == '{')
		{
			if (!check_commas(line, i + 1))
				return (0);
			i += next_bracket(line, '{', i);
		}
	}
	return (1);
}

int		next_comma(char *str, int i)
{
	FT_INIT(int, ret, 0);
	while (str[i])
	{
		if (str[i] == '{')
		{
			ret += next_bracket(str, '{', i) + 1;
			i += next_bracket(str, '{', i) + 1;
		}
		else if (str[i] == ',')
			return (ret);
		else
		{
			i++;
			ret++;
		}
	}
	return (-1);
}

int		is_bracket_in_exp(char *str, int i)
{
	FT_INIT(int, count, 0);
	while (str[i])
	{
		if (str[i] == '}')
			count++;
		i++;
	}
	return (count);
}

int		end_bracket(char *str, int i)
{
	FT_INIT(int, len, 0);
	while (str[i] && str[i] != '}')
	{
		i++;
		len++;
	}
	return (len);
}

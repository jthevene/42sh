/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commas_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:36:40 by hjacque           #+#    #+#             */
/*   Updated: 2017/04/10 14:58:34 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/globing.h"

int		count_commas(char *line, int i)
{
	FT_INIT(int, count, 0);
	FT_INIT(int, tmp, 0);
	if (line[i] && line[i] == '{')
		i++;
	while (i < (int)ft_strlen(line) && line[i])
	{
		if (line[i] == ',')
			count++;
		if (line[i] == '{')
		{
			if (!(tmp = count_commas(line, i + 1)))
				return (0);
			i += next_bracket(line, '{', i) + 1;
			count += line[i] && line[i] == ',' ? 1 : 0;
		}
		if (line[i] && line[i] == '}')
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
		return (1);
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

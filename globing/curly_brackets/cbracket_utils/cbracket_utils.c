/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cbracket_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 19:33:32 by sgaudin           #+#    #+#             */
/*   Updated: 2017/04/10 14:58:36 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/globing.h"

int					last_bracket(char *str, int c)
{
	FT_INIT(int, i, 0);
	FT_INIT(int, ret, 0);
	FT_INIT(int, count, c);
	while (str[i])
		i++;
	--i;
	ret = i;
	while (str[i])
	{
		if (str[i] == '{')
		{
			count--;
			if (!count)
				break ;
		}
		i--;
		ret--;
	}
	return (ret);
}

char				*next_expr(char *str, int i)
{
	FT_INIT(int, ret, 0);
	FT_INIT(int, j, 0);
	while (str[i] && str[i] != ' ')
		i--;
	i++;
	j = i;
	while (str[i])
	{
		if (str[i] == '{' || str[i] == '[')
		{
			ret += next_bracket(str, str[i], i);
			i += next_bracket(str, str[i], i);
		}
		if (str[i] == ' ')
			break ;
		i++;
		ret++;
	}
	return (ft_strsub(str, j, ret));
}

void				free_double_tab(char ***tabl)
{
	if ((*tabl))
	{
		if ((*tabl)[0])
			free((*tabl)[0]);
		if ((*tabl)[1])
			free((*tabl)[1]);
		free((*tabl));
	}
}

int					detect_double_bracket(char *str)
{
	FT_INIT(int, i, 0);
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '{' && str[i + 1] == '{')
			return (1);
		i++;
	}
	return (0);
}

char				**recup_ext_args(char *str)
{
	FT_INIT(char **, args, NULL);
	FT_INIT(int, i, 0);
	FT_INIT(int, j, 0);
	FT_INIT(int, len, 0);
	if (!(args = (char **)malloc(sizeof(char *) * 3)))
		return (NULL);
	if (str[i] != '{')
		while (str[i] != '{')
			i++;
	args[0] = i > 0 ? ft_strsub(str, 0, i) : NULL;
	while (str[i])
		i++;
	if (str[--i] != '}')
		while (str[i] != '}')
			i--;
	j = i + 1;
	while (str[j])
	{
		j++;
		len++;
	}
	args[1] = len > 0 ? ft_strsub(str, i + 1, len) : NULL;
	args[2] = NULL;
	return (args);
}

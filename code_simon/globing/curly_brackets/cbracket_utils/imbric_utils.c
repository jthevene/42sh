/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imbric_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 08:54:11 by sgaudin           #+#    #+#             */
/*   Updated: 2016/11/24 08:54:13 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/globing.h"

int					last_bracket(char *str)
{
	FT_INIT(int, i, 0);
	FT_INIT(int, ret, 0);
	while (str[i])
		i++;
	--i;
	ret = i;
	while (str[i] != '{')
	{
		i--;
		ret--;
	}
	return (ret);
}

int					i_get_arg_len(char *str, int i, int type)
{
	FT_INIT(int, ret, 0);
	if (type == ARG)
	{
		while (str[i] != '\0' && str[i] != ',' && str[i] != '}')
		{
			i++;
			ret++;
		}
	}
	else if (type == BEGIN)
	{
		while (str[i] != '\0' && str[i] != ',' && str[i] != '}' && str[i] != '{')
		{
			i--;
			ret++;
		}
	}
	else if (type == END)
	{
		while (str[i] && str[i] != '}' && str[i] != '{' && str[i] != ',')
		{
			i++;
			ret++;
		}
	}
	return (ret);
}

char				**i_get_arg_ext(char *str)
{
	FT_INIT(char **, i_tab, NULL);
	FT_INIT(int, i, last_bracket(str));
	FT_INIT(int, begin_len, i_get_arg_len(str, i - 1, BEGIN));
	FT_INIT(int, end_len, 0);
	if (!(i_tab = (char **)malloc(sizeof(char *) * 2)))
		return (NULL);
	i_tab[0] = !begin_len ? NULL : ft_strsub(str, i - begin_len, begin_len);
	while (str[i] != '}')
		i++;
	end_len = i_get_arg_len(str, i + 1, END);
	i_tab[1] = !end_len ? NULL : ft_strsub(str, i + 1, end_len);
	return (i_tab);
}

int					i_get_expr_end(char *str)
{
	FT_INIT(int, i, last_bracket(str));
	while (str[i] != '}')
		i++;
	i++;
	while (str[i] && str[i] != '}' && str[i] != ',')
		i++;
	return (i);
}
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

int					i_get_arg_len(char *str, int i, int type, t_glob *glob)
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
		while (i >= 0 && str[i] != '\0' && str[i] != ',' && str[i] != '}' && str[i] != '{')
		{
			i--;
			ret++;
		}
		glob->c_touch = str[i] == '}' ? TRUE : FALSE;
	}
	else if (type == END)
	{
		while (str[i] && str[i] != '}' && str[i] != '{' && str[i] != ',')
		{
			i++;
			ret++;
		}
		glob->c_touch = str[i] == '{' ? TRUE : glob->c_touch;
	}
	return (ret);
}

char				**i_get_arg_ext(char *str, t_glob *glob)
{
	FT_INIT(char **, i_tab, NULL);
	FT_INIT(int, i, last_bracket(str, glob->lastb_count));
	FT_INIT(int, begin_len, i_get_arg_len(str, i - 1, BEGIN, glob));
	FT_INIT(int, end_len, 0);
	if (!(i_tab = (char **)malloc(sizeof(char *) * 3)))
		return (NULL);
	i_tab[0] = !begin_len ? NULL : ft_strsub(str, i - begin_len, begin_len);
	while (str[i] != '}')
		i++;
	end_len = i_get_arg_len(str, i + 1, END, glob);
	i_tab[1] = !end_len ? NULL : ft_strsub(str, i + 1, end_len);
	i_tab[2] = NULL;
	return (i_tab);
}

int					i_get_expr_end(char *str, int lastb_count)
{
	FT_INIT(int, i, last_bracket(str, lastb_count));
	while (str[i] != '}')
		i++;
	i++;
	while (str[i] && str[i] != '{' && str[i] != '}' && str[i] != ',')
		i++;
	return (i);
}

char				*i_next_bracket(char *str)
{
	FT_INIT(int, i, 0);
	FT_INIT(int, nb, 0);
	while (str[i])
	{
		if (str[i] == '{')
		{
			if (!nb)
				nb++;
			else
				return (ft_strsub(str, i, ft_abs(i - ft_strlen(str))));
		}
		i++;
	}
	return (NULL);
}
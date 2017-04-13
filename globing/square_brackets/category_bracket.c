/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   category_bracket.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 18:40:11 by sgaudin           #+#    #+#             */
/*   Updated: 2017/04/13 11:00:26 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/globing.h"

static char				*category_choice(char *category, t_glob *glob)
{
	if (!ft_strcmp(category, "upper"))
		return (glob->upper);
	else if (!ft_strcmp(category, "lower"))
		return (glob->lower);
	else if (!ft_strcmp(category, "alpha"))
		return (glob->alpha);
	else if (!ft_strcmp(category, "digit"))
		return (glob->digit);
	else if (!ft_strcmp(category, "alnum"))
		return (glob->alnum);
	else if (!ft_strcmp(category, "space"))
		return (glob->space);
	else if (!ft_strcmp(category, "graph"))
		return (glob->graph);
	else if (!ft_strcmp(category, "print"))
		return (glob->print);
	else if (!ft_strcmp(category, "punct"))
		return (glob->punct);
	else if (!ft_strcmp(category, "cntrl"))
		return (glob->cntrl);
	else if (!ft_strcmp(category, "xdigit"))
		return (glob->xdigit);
	else
		return (NULL);
}

int						detect_category(char *str)
{
	FT_INIT(int, i, 0);
	FT_INIT(int, j, 0);
	while (str[i])
	{
		if (str[i] == '[')
		{
			j = i;
			if (str[j + 1] == ':')
			{
				while (str[j] && str[j] != ']')
				{
					if (str[j - 1] == ':')
						return (1);
					j++;
				}
			}
		}
		i++;
	}
	return (0);
}

static char				*replace_category(char *str, t_glob *glob)
{
	FT_INIT(char *, ret, NULL);
	FT_INIT(char *, category, get_category(str));
	FT_INIT(char *, tmp_cat, ft_strdup(category_choice(category, glob)));
	FT_INIT(int, i, 0);
	FT_INIT(int, j, -1);
	FT_INIT(int, check, 0);
	ret = ft_strnew(ft_strlen(category_choice(category, glob))
		+ ft_strlen(str) - ft_strlen(category) - 4);
	ret[++j] = '[';
	if (str[1] == '^')
		ret[++j] = '^';
	while (tmp_cat[i])
		ret[++j] = tmp_cat[i++];
	free(tmp_cat);
	i = str[1] == '^' ? 2 : 1;
	while (str[i])
	{
		if (str[i] == '[' && str[i + 1] == ':' && !check++)
			i = i + ft_strlen(category) + 4;
		ret[++j] = str[i];
		i++;
	}
	ret[++j] = '\0';
	free(category);
	return (ret);
}

char					*handle_categories(char *str, t_glob *glob)
{
	FT_INIT(char *, tmp, ft_strdup(str));
	FT_INIT(char *, tmp2, NULL);
	while (1)
	{
		if (!detect_category(tmp))
			break ;
		tmp2 = ft_strdup(tmp);
		ft_strdel(&tmp);
		tmp = replace_category(tmp2, glob);
		ft_strdel(&tmp2);
	}
	return (tmp);
}

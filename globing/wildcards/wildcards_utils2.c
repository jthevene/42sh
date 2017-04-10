/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 18:40:12 by sgaudin           #+#    #+#             */
/*   Updated: 2017/04/10 14:57:39 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/globing.h"

static int		is_only_qmark_and_star(char *str)
{
	FT_INIT(int, i, 0);
	FT_INIT(int, star, 0);
	while (str[i])
	{
		if (str[i] == '*')
			star++;
		if (str[i] == '*' || str[i] == '?')
			i++;
		else
			return (0);
	}
	if (star >= 1)
		return (1);
	else
		return (0);
}

int				g_parse_expr(char *str, t_glob *glob)
{
	if (!ft_strchr(str, '?') && !ft_strchr(str, '[') && !ft_strchr(str, '*'))
		return (g_no_token(str, glob));
	else if ((ft_strchr(str, '?') && !ft_strchr_bslash(str, '?'))
		|| (ft_strchr(str, '[') && !ft_strchr_bslash(str, '['))
		|| (ft_strchr(str, '*') && !ft_strchr_bslash(str, '*')))
		return (g_no_token(str, glob));
	else if (is_only_qmark_and_star(str))
		return (only_qmark(str, TRUE, glob));
	else if (is_only_token('?', str))
		return (only_qmark(str, FALSE, glob));
	else if (is_only_token('[', str))
		return (only_cbrkt(str, glob));
	else if (is_only_token('*', str))
		return (only_star(str, glob));
	else if (ft_strchr(str, '*'))
		return (mix_with_star(str, glob));
	else
		return (mix_token(str, glob));
}

int				push_content_path(t_bracket **l, char *s, t_glob *g)
{
	FT_INIT(char *, tmp, NULL);
	if (s[0] == '.')
	{
		free(s);
		return (0);
	}
	if (!bracket_pushback(l))
		return (0);
	if (g->f_path)
		tmp = ft_strjoin(g->f_path, s);
	else
		tmp = ft_strdup(s);
	if (g->l_path)
		(*l)->content = ft_strjoin(tmp, g->l_path);
	else
		(*l)->content = ft_strdup(tmp);
	free(s);
	free(tmp);
	return (1);
}

int				ft_check_bracket(char *s1, int i, int stop, t_glob *g)
{
	FT_INIT(int, ret, 0);
	FT_INIT(char, last, i - 1 >= 0 ? s1[i - 1] : '\0');
	while (s1[i])
	{
		if (last)
		{
			if (ft_strchr(g->sbracket->content, s1[i]) && s1[i - 1] == last)
			{
				if (stop == TRUE)
					return (i);
				else
					ret = i;
			}
		}
		else if (ft_strchr(g->sbracket->content, s1[i]))
		{
			if (stop == TRUE)
				return (i);
			else
				ret = i;
		}
		i++;
	}
	return (ret);
}

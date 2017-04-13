/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 11:15:42 by sgaudin           #+#    #+#             */
/*   Updated: 2017/04/13 10:18:43 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/globing.h"

t_bracket		*expansion_args(char *s, char *s2)
{
	FT_INIT(t_bracket *, args, NULL);
	FT_INIT(int, c, s[0]);
	FT_INIT(int, c2, s2[0]);
	FT_INIT(int, inc, c < c2 ? 1 : -1);
	if (exp_type(s) == CHARS || exp_type(s2) == CHARS)
	{
		while (c - inc != c2)
		{
			bracket_pushback(&args);
			args->content = ft_cdup(c);
			c += inc;
		}
		return (args);
	}
	c = ft_atoi(s);
	c2 = ft_atoi(s2);
	inc = c < c2 ? 1 : -1;
	while (c - inc != c2)
	{
		bracket_pushback(&args);
		args->content = ft_itoa(c);
		c += inc;
	}
	return (args);
}

int				e_solo(char *exp, int i, t_bracket *args, t_glob *glob)
{
	FT_INIT(char *, tmp, NULL);
	FT_INIT(char *, tmp2, NULL);
	tmp = ft_strsub(exp, 0, i - 1);
	glob->exp = ft_strjoin(tmp, args->content);
	free(tmp);
	while (exp[i] != '}')
		i++;
	tmp = ft_strdup(glob->exp);
	tmp2 = ft_strsub(exp, i + 1, ft_strlen(exp) - i - 1);
	free(glob->exp);
	glob->exp = ft_strjoin(tmp, tmp2);
	free(tmp);
	free(tmp2);
	free_tbracket(&args);
	return (1);
}

int				e_recreate(char *exp, int i, t_bracket *args, t_glob *glob)
{
	FT_INIT(char *, tmp, NULL);
	FT_INIT(char *, tmp2, NULL);
	if (glob->exp)
		free(glob->exp);
	if (is_solo_arg(args))
		return (e_solo(exp, i, args, glob));
	tmp = ft_strsub(exp, 0, i);
	rewind_tbracket(&args);
	while (args->next)
	{
		tmp2 = ft_strjoin(args->content, ",");
		glob->exp = ft_strjoin(tmp, tmp2);
		free_triple_str(&tmp, &tmp2, NULL);
		tmp = ft_strdup(glob->exp);
		free(glob->exp);
		args = args->next;
	}
	while (exp[i] != '}')
		i++;
	glob->exp = ft_strsub(exp, i, ft_strlen(exp) - i);
	tmp2 = ft_strjoin(args->content, glob->exp);
	free(glob->exp);
	glob->exp = ft_strjoin(tmp, tmp2);
	free_triple_str(&tmp, &tmp2, NULL);
	return (free_tbracket(&args));
}

int				is_valid_expansion(char *exp, int i, t_glob *glob)
{
	FT_INIT(int, j, i - 1);
	FT_INIT(int, k, 0);
	FT_INIT(char *, s, NULL);
	FT_INIT(char *, s2, NULL);
	while (exp[++j] != '.')
		k++;
	s = k ? ft_strsub(exp, i, k) : NULL;
	j++;
	k = 0;
	while (exp[++j] != '}')
		k++;
	s2 = k ? ft_strsub(exp, j - k, k) : NULL;
	if (!s || !s2 || exp_type(s) == BOTH || exp_type(s2) == BOTH
	|| (exp_type(s) == DIGIT && ft_strlen(s) >= 1 && exp_type(s2) == CHARS)
	|| (exp_type(s2) == DIGIT && ft_strlen(s2) >= 1 && exp_type(s) == CHARS)
	|| (exp_type(s) == CHARS && ft_strlen(s) > 1)
	|| (exp_type(s2) == CHARS && ft_strlen(s2) > 1))
	{
		free_triple_str(&s, &s2, &exp);
		return (0);
	}
	e_recreate(exp, i, expansion_args(s, s2), glob);
	free_triple_str(&s, &s2, NULL);
	ft_strdel(&exp);
	return (1);
}

int				hub_expansion(char *str, t_glob *glob)
{
	FT_INIT(int, i, 0);
	FT_INIT(int, j, 0);
	while (str[i])
	{
		if (str[i] == '{')
		{
			j = i;
			while (str[j] && str[j] != '}')
			{
				if (str[j] == '.' && str[j + 1] && str[j + 1] == '.'
					&& str[j + 2] && ft_isalnum(str[j + 2]))
				{
					if (!is_valid_expansion(str, i + 1, glob))
						return (0);
					else
						str = ft_strdup(glob->exp);
					j += 2;
				}
				j = str[++j] == '{' ? j + next_bracket(str, '{', i) : j;
			}
		}
		i++;
	}
	free(str);
	return (1);
}

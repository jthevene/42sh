/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 11:00:05 by sgaudin           #+#    #+#             */
/*   Updated: 2016/12/02 11:00:06 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/globing.h"

void			replace_expansion(char *exp, int i)
{
	if (exp && i)
		printf("/~~~~~ replace_expansion here ~~~~~/\n");
	else
		printf("/~~~~~ replace_expansion here ~~~~~/\n");
}

int				is_valid_expansion(char *exp, int i)
{
	FT_INIT(int, j, 0);
	FT_INIT(int, k, 0);
	FT_INIT(char *, s, NULL);
	FT_INIT(char *, s2, NULL);
	while (exp[j] != '.')
		j++;
	s = j ? ft_strsub(exp, i, j - 1) : NULL;
	j++;
	while (exp[++j] != '}')
		k++;
	s2 = k ? ft_strsub(exp, j - k, k) : NULL;
	if (!s || !s2 || exp_type(s) == BOTH || exp_type(s2) == BOTH)
		return (0);
	if ((exp_type(s) == DIGIT && ft_strlen(s) > 1 && exp_type(s2) == CHARS)
	|| (exp_type(s2) == DIGIT && ft_strlen(s2) > 1 && exp_type(s) == CHARS)
	|| (exp_type(s) == CHARS && ft_strlen(s) > 1)
	|| (exp_type(s2) == CHARS && ft_strlen(s2) > 1))
		return (0);
	if (s)
		free(s);
	if (s2)
		free(s2);
	return (1);
}

void			hub_expansion(char *str, t_glob *glob)
{
	FT_INIT(int, i, 0);
	FT_INIT(int, j, 0);
	if (glob)
		printf("hub_expansion\n");
	while (str[i])
	{
		if (str[i] == '{')
		{
			j = i;
			while (str[j] != '}')
			{
				if (str[j] == '.' && str[j + 1] == '.')
				{
					if (is_valid_expansion(str, i + 1))
						replace_expansion(str, i);
					else
						printf("/!!!!!! Expansion is not valid !!!!!!/\n");
					j += 2;
				}
				j++;
			}
		}
		i++;
	}
}
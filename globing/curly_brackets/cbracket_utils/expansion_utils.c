/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjacque <hjacque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:36:40 by hjacque           #+#    #+#             */
/*   Updated: 2017/03/08 14:46:27 by hjacque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/globing.h"

int			exp_type(char *str)
{
	FT_INIT(int, i, 0);
	FT_INIT(int, chars, 0);
	FT_INIT(int, digit, 0);
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			digit = 1;
		else if (ft_isalpha(str[i]))
			chars = 1;
		else
			chars = 0;
		i++;
	}
	if (digit && chars)
		return (BOTH);
	else if (digit && !chars)
		return (DIGIT);
	else if (!digit && chars)
		return (CHARS);
	return (BOTH);
}

char		*ft_cdup(char c)
{
	FT_INIT(char *, new, ft_strnew(1));
	new[0] = c;
	new[1] = '\0';
	return (new);
}

int			is_solo_arg(t_bracket *args)
{
	FT_INIT(int, count, 0);
	rewind_tbracket(&args);
	while (args->next)
	{
		args = args->next;
		count++;
	}
	count++;
	return (count == 1 ? 1 : 0);
}

void		free_double_str(char **s, char **s2)
{
	if ((*s) != NULL)
	{
		free((*s));
		(*s) = NULL;
	}
	if ((*s2) != NULL)
	{
		free((*s2));
		(*s2) = NULL;
	}
}

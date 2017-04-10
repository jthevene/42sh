/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 18:40:12 by sgaudin           #+#    #+#             */
/*   Updated: 2017/04/10 14:58:00 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/globing.h"
#include "../../../includes/redir.h"

char		*get_rng_str(char *str, int i)
{
	char	*rng_str;

	rng_str = NULL;
	rng_str = ft_strsub(str, i - 1, 3);
	return (rng_str);
}

int			get_len_mix(char *str)
{
	FT_INIT(int, i, 0);
	FT_INIT(int, len, 0);
	FT_INIT(char *, tmp, NULL);
	tmp = ft_strchr(str, '[') && ft_strchr(str, ']')
	? clean_brackets(str) : ft_strdup(str);
	while (tmp[i])
	{
		if (tmp[i] == '-' && tmp[i + 1] && tmp[i - 1])
		{
			len += tmp[i + 1] - tmp[i - 1];
			i++;
		}
		else
			len++;
		i++;
	}
	free(tmp);
	return (len);
}

int			get_letters(char **ret, char *str)
{
	FT_INIT(int, i, 0);
	FT_INIT(int, j, 0);
	FT_INIT(int, k, 0);
	while (str[i])
	{
		if (str[i] == '-' && str[i - 1] && str[i + 1])
		{
			while (j < i - 1)
			{
				(*ret)[k] = str[j];
				j++;
				k++;
			}
			j += 3;
			i++;
		}
		i++;
	}
	while (str[j])
	{
		(*ret)[k] = str[j];
		j++;
		k++;
	}
	return (0);
}

char		*get_category(char *str)
{
	FT_INIT(char *, category, NULL);
	FT_INIT(int, i, -1);
	FT_INIT(int, j, 0);
	while (str[++i])
	{
		if (str[i] == '[' && str[i + 1] == ':')
		{
			j = i + 2;
			while (str[i++])
				if (str[i] == ']' && str[i - 1] == ':')
					break ;
			category = ft_strsub(str, j, i - j - 1);
			break ;
		}
	}
	return (category);
}

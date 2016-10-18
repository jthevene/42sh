/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 15:01:24 by sgaudin           #+#    #+#             */
/*   Updated: 2016/10/14 15:01:47 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/redir.h"
#include "../includes/globing.h"

char		*clean_brackets(char *str) // enleve les []
{
	int		start;

	FT_INIT(int, i, 0);
	FT_INIT(int, len, 0);
	FT_INIT(char *, ret, NULL);
	while (str[i] && str[i] != '[')
		i++;
	start = i + 1;
	i++;
	while (str[i] && str[i] != ']')
	{
		i++;
		len++;
	}
	if (!(ret = (char *)malloc(sizeof(char) * len)))
		return (NULL);
	i = 0;
	while (i < len)
	{
		ret[i] = str[start];
		i++;
		start++;
	}
	ret[i] = '\0';
	return (ret);
}

char		*get_rng_str(char *str, int i)// uac-rgs => "c-r"
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
	FT_INIT(char *, tmp, clean_brackets(str));
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

int			check_rng(char *str)
{
	FT_INIT(int, i, 0);
	FT_INIT(char *, tmp, clean_brackets(str));
	if (!ft_strchr(tmp, '-'))
	{
		free(tmp);
		return (1);
	}
	while (tmp[i])
	{
		if (tmp[i] == '-' && tmp[i - 1] && tmp[i + 1] 
			&& tmp[i + 1] != ']' && tmp[i - 1] != '[')
		{
			if (tmp[i - 1] > tmp[i + 1])
			{
				free(tmp);
				return (0);
			}
			i++;
		}
		i++;
	}
	free(tmp);
	return (1);
}
